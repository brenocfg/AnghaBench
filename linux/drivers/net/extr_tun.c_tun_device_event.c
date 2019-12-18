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
struct tun_struct {int numqueues; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_3__ {TYPE_2__* sk; } ;
struct tun_file {TYPE_1__ socket; } ;
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sk_write_space ) (TYPE_2__*) ;} ;

/* Variables and functions */
#define  NETDEV_CHANGE_TX_QUEUE_LEN 129 
#define  NETDEV_UP 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 struct tun_file* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  tun_link_ops ; 
 int /*<<< orphan*/  tun_queue_resize (struct tun_struct*) ; 

__attribute__((used)) static int tun_device_event(struct notifier_block *unused,
			    unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct tun_struct *tun = netdev_priv(dev);
	int i;

	if (dev->rtnl_link_ops != &tun_link_ops)
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_CHANGE_TX_QUEUE_LEN:
		if (tun_queue_resize(tun))
			return NOTIFY_BAD;
		break;
	case NETDEV_UP:
		for (i = 0; i < tun->numqueues; i++) {
			struct tun_file *tfile;

			tfile = rtnl_dereference(tun->tfiles[i]);
			tfile->socket.sk->sk_write_space(tfile->socket.sk);
		}
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}