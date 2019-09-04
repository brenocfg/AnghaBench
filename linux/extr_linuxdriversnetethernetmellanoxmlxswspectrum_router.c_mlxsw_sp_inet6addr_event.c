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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_inet6addr_event_work {unsigned long event; int /*<<< orphan*/  work; struct net_device* dev; } ;
struct inet6_ifaddr {TYPE_1__* idev; } ;
struct TYPE_2__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long NETDEV_UP ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct mlxsw_sp_inet6addr_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_inet6addr_event_work ; 
 int /*<<< orphan*/  mlxsw_sp_port_dev_lower_find_rcu (struct net_device*) ; 

int mlxsw_sp_inet6addr_event(struct notifier_block *unused,
			     unsigned long event, void *ptr)
{
	struct inet6_ifaddr *if6 = (struct inet6_ifaddr *) ptr;
	struct mlxsw_sp_inet6addr_event_work *inet6addr_work;
	struct net_device *dev = if6->idev->dev;

	/* NETDEV_UP event is handled by mlxsw_sp_inet6addr_valid_event */
	if (event == NETDEV_UP)
		return NOTIFY_DONE;

	if (!mlxsw_sp_port_dev_lower_find_rcu(dev))
		return NOTIFY_DONE;

	inet6addr_work = kzalloc(sizeof(*inet6addr_work), GFP_ATOMIC);
	if (!inet6addr_work)
		return NOTIFY_BAD;

	INIT_WORK(&inet6addr_work->work, mlxsw_sp_inet6addr_event_work);
	inet6addr_work->dev = dev;
	inet6addr_work->event = event;
	dev_hold(dev);
	mlxsw_core_schedule_work(&inet6addr_work->work);

	return NOTIFY_DONE;
}