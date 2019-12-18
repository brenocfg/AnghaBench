#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {unsigned int thread_events; unsigned int sysfs_events; int state; int /*<<< orphan*/  dev; int /*<<< orphan*/  skt_mutex; TYPE_2__* callback; int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread_done; int /*<<< orphan*/ * thread; int /*<<< orphan*/  socket; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* suspend ) (struct pcmcia_socket*) ;int /*<<< orphan*/  (* requery ) (struct pcmcia_socket*) ;int /*<<< orphan*/  (* resume ) (struct pcmcia_socket*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 unsigned int PCMCIA_UEVENT_EJECT ; 
 unsigned int PCMCIA_UEVENT_INSERT ; 
 unsigned int PCMCIA_UEVENT_REQUERY ; 
 unsigned int PCMCIA_UEVENT_RESUME ; 
 unsigned int PCMCIA_UEVENT_SUSPEND ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_PRESENT ; 
 unsigned int SS_DETECT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * current ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pccard_sysfs_add_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pccard_sysfs_remove_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  socket_detect_change (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_insert (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_remove (struct pcmcia_socket*) ; 
 int socket_resume (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  socket_suspend (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int stub3 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub4 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub5 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 

__attribute__((used)) static int pccardd(void *__skt)
{
	struct pcmcia_socket *skt = __skt;
	int ret;

	skt->thread = current;
	skt->socket = dead_socket;
	skt->ops->init(skt);
	skt->ops->set_socket(skt, &skt->socket);

	/* register with the device core */
	ret = device_register(&skt->dev);
	if (ret) {
		dev_warn(&skt->dev, "PCMCIA: unable to register socket\n");
		skt->thread = NULL;
		complete(&skt->thread_done);
		return 0;
	}
	ret = pccard_sysfs_add_socket(&skt->dev);
	if (ret)
		dev_warn(&skt->dev, "err %d adding socket attributes\n", ret);

	complete(&skt->thread_done);

	/* wait for userspace to catch up */
	msleep(250);

	set_freezable();
	for (;;) {
		unsigned long flags;
		unsigned int events;
		unsigned int sysfs_events;

		spin_lock_irqsave(&skt->thread_lock, flags);
		events = skt->thread_events;
		skt->thread_events = 0;
		sysfs_events = skt->sysfs_events;
		skt->sysfs_events = 0;
		spin_unlock_irqrestore(&skt->thread_lock, flags);

		mutex_lock(&skt->skt_mutex);
		if (events & SS_DETECT)
			socket_detect_change(skt);

		if (sysfs_events) {
			if (sysfs_events & PCMCIA_UEVENT_EJECT)
				socket_remove(skt);
			if (sysfs_events & PCMCIA_UEVENT_INSERT)
				socket_insert(skt);
			if ((sysfs_events & PCMCIA_UEVENT_SUSPEND) &&
				!(skt->state & SOCKET_CARDBUS)) {
				if (skt->callback)
					ret = skt->callback->suspend(skt);
				else
					ret = 0;
				if (!ret) {
					socket_suspend(skt);
					msleep(100);
				}
			}
			if ((sysfs_events & PCMCIA_UEVENT_RESUME) &&
				!(skt->state & SOCKET_CARDBUS)) {
				ret = socket_resume(skt);
				if (!ret && skt->callback)
					skt->callback->resume(skt);
			}
			if ((sysfs_events & PCMCIA_UEVENT_REQUERY) &&
				!(skt->state & SOCKET_CARDBUS)) {
				if (!ret && skt->callback)
					skt->callback->requery(skt);
			}
		}
		mutex_unlock(&skt->skt_mutex);

		if (events || sysfs_events)
			continue;

		if (kthread_should_stop())
			break;

		set_current_state(TASK_INTERRUPTIBLE);

		schedule();

		/* make sure we are running */
		__set_current_state(TASK_RUNNING);

		try_to_freeze();
	}

	/* shut down socket, if a device is still present */
	if (skt->state & SOCKET_PRESENT) {
		mutex_lock(&skt->skt_mutex);
		socket_remove(skt);
		mutex_unlock(&skt->skt_mutex);
	}

	/* remove from the device core */
	pccard_sysfs_remove_socket(&skt->dev);
	device_unregister(&skt->dev);

	return 0;
}