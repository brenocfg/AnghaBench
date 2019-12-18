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
struct pcmcia_socket {int state; int /*<<< orphan*/  ops_mutex; TYPE_1__* callback; int /*<<< orphan*/  dev; int /*<<< orphan*/  sock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* add ) (struct pcmcia_socket*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int SOCKET_CARDBUS ; 
 int SOCKET_CARDBUS_CONFIG ; 
 int SOCKET_INUSE ; 
 int SOCKET_PRESENT ; 
 int /*<<< orphan*/  cb_alloc (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_delay ; 
 int socket_setup (struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_shutdown (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_socket*) ; 

__attribute__((used)) static int socket_insert(struct pcmcia_socket *skt)
{
	int ret;

	dev_dbg(&skt->dev, "insert\n");

	mutex_lock(&skt->ops_mutex);
	if (skt->state & SOCKET_INUSE) {
		mutex_unlock(&skt->ops_mutex);
		return -EINVAL;
	}
	skt->state |= SOCKET_INUSE;

	ret = socket_setup(skt, setup_delay);
	if (ret == 0) {
		skt->state |= SOCKET_PRESENT;

		dev_notice(&skt->dev, "pccard: %s card inserted into slot %d\n",
			   (skt->state & SOCKET_CARDBUS) ? "CardBus" : "PCMCIA",
			   skt->sock);

#ifdef CONFIG_CARDBUS
		if (skt->state & SOCKET_CARDBUS) {
			cb_alloc(skt);
			skt->state |= SOCKET_CARDBUS_CONFIG;
		}
#endif
		dev_dbg(&skt->dev, "insert done\n");
		mutex_unlock(&skt->ops_mutex);

		if (!(skt->state & SOCKET_CARDBUS) && (skt->callback))
			skt->callback->add(skt);
	} else {
		mutex_unlock(&skt->ops_mutex);
		socket_shutdown(skt);
	}

	return ret;
}