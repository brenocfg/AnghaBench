#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pvrdma_netdevice_work {unsigned long event; int /*<<< orphan*/  work; struct net_device* event_netdev; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  event_wq ; 
 struct pvrdma_netdevice_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  pvrdma_netdevice_event_work ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvrdma_netdevice_event(struct notifier_block *this,
				  unsigned long event, void *ptr)
{
	struct net_device *event_netdev = netdev_notifier_info_to_dev(ptr);
	struct pvrdma_netdevice_work *netdev_work;

	netdev_work = kmalloc(sizeof(*netdev_work), GFP_ATOMIC);
	if (!netdev_work)
		return NOTIFY_BAD;

	INIT_WORK(&netdev_work->work, pvrdma_netdevice_event_work);
	netdev_work->event_netdev = event_netdev;
	netdev_work->event = event;
	queue_work(event_wq, &netdev_work->work);

	return NOTIFY_DONE;
}