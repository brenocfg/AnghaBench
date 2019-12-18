#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcmcia_socket {int state; int /*<<< orphan*/  skt_mutex; TYPE_1__* callback; int /*<<< orphan*/  ops_mutex; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct pcmcia_socket*) ;int /*<<< orphan*/  (* suspend ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int EPERM ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_PRESENT ; 
 int SOCKET_SUSPEND ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int socket_reset (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub2 (struct pcmcia_socket*) ; 

int pcmcia_reset_card(struct pcmcia_socket *skt)
{
	int ret;

	dev_dbg(&skt->dev, "resetting socket\n");

	mutex_lock(&skt->skt_mutex);
	do {
		if (!(skt->state & SOCKET_PRESENT)) {
			dev_dbg(&skt->dev, "can't reset, not present\n");
			ret = -ENODEV;
			break;
		}
		if (skt->state & SOCKET_SUSPEND) {
			dev_dbg(&skt->dev, "can't reset, suspended\n");
			ret = -EBUSY;
			break;
		}
		if (skt->state & SOCKET_CARDBUS) {
			dev_dbg(&skt->dev, "can't reset, is cardbus\n");
			ret = -EPERM;
			break;
		}

		if (skt->callback)
			skt->callback->suspend(skt);
		mutex_lock(&skt->ops_mutex);
		ret = socket_reset(skt);
		mutex_unlock(&skt->ops_mutex);
		if ((ret == 0) && (skt->callback))
			skt->callback->resume(skt);

		ret = 0;
	} while (0);
	mutex_unlock(&skt->skt_mutex);

	return ret;
}