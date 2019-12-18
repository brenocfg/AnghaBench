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
struct pcmcia_socket {int state; int /*<<< orphan*/  dev; TYPE_2__* ops; int /*<<< orphan*/  ops_mutex; scalar_t__ functions; int /*<<< orphan*/ * fake_cis; scalar_t__ lock_count; int /*<<< orphan*/  socket; TYPE_1__* callback; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_status ) (struct pcmcia_socket*,int*) ;int /*<<< orphan*/  (* set_socket ) (struct pcmcia_socket*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct pcmcia_socket*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int SOCKET_INUSE ; 
 int SOCKET_PRESENT ; 
 int SS_POWERON ; 
 int /*<<< orphan*/  cb_free (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int shutdown_delay ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub3 (struct pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct pcmcia_socket*,int*) ; 

__attribute__((used)) static void socket_shutdown(struct pcmcia_socket *s)
{
	int status;

	dev_dbg(&s->dev, "shutdown\n");

	if (s->callback)
		s->callback->remove(s);

	mutex_lock(&s->ops_mutex);
	s->state &= SOCKET_INUSE | SOCKET_PRESENT;
	msleep(shutdown_delay * 10);
	s->state &= SOCKET_INUSE;

	/* Blank out the socket state */
	s->socket = dead_socket;
	s->ops->init(s);
	s->ops->set_socket(s, &s->socket);
	s->lock_count = 0;
	kfree(s->fake_cis);
	s->fake_cis = NULL;
	s->functions = 0;

	/* From here on we can be sure that only we (that is, the
	 * pccardd thread) accesses this socket, and all (16-bit)
	 * PCMCIA interactions are gone. Therefore, release
	 * ops_mutex so that we don't get a sysfs-related lockdep
	 * warning.
	 */
	mutex_unlock(&s->ops_mutex);

#ifdef CONFIG_CARDBUS
	cb_free(s);
#endif

	/* give socket some time to power down */
	msleep(100);

	s->ops->get_status(s, &status);
	if (status & SS_POWERON) {
		dev_err(&s->dev,
			"*** DANGER *** unable to remove socket power\n");
	}

	s->state &= ~SOCKET_INUSE;
}