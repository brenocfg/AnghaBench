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
typedef  int /*<<< orphan*/  u8 ;
struct switchdev_notifier_fdb_info {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {void* addr; } ;
struct rocker_switchdev_event_work {unsigned long event; int /*<<< orphan*/  work; TYPE_2__ fdb_info; struct rocker_port* rocker_port; } ;
struct rocker_port {TYPE_1__* rocker; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rocker_owq; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
#define  SWITCHDEV_FDB_ADD_TO_DEVICE 129 
#define  SWITCHDEV_FDB_DEL_TO_DEVICE 128 
 unsigned long SWITCHDEV_PORT_ATTR_SET ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rocker_switchdev_event_work*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,void*,int) ; 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rocker_port_dev_check (struct net_device*) ; 
 int /*<<< orphan*/  rocker_switchdev_event_work ; 
 int rocker_switchdev_port_attr_set_event (struct net_device*,void*) ; 
 struct net_device* switchdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int rocker_switchdev_event(struct notifier_block *unused,
				  unsigned long event, void *ptr)
{
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	struct rocker_switchdev_event_work *switchdev_work;
	struct switchdev_notifier_fdb_info *fdb_info = ptr;
	struct rocker_port *rocker_port;

	if (!rocker_port_dev_check(dev))
		return NOTIFY_DONE;

	if (event == SWITCHDEV_PORT_ATTR_SET)
		return rocker_switchdev_port_attr_set_event(dev, ptr);

	rocker_port = netdev_priv(dev);
	switchdev_work = kzalloc(sizeof(*switchdev_work), GFP_ATOMIC);
	if (WARN_ON(!switchdev_work))
		return NOTIFY_BAD;

	INIT_WORK(&switchdev_work->work, rocker_switchdev_event_work);
	switchdev_work->rocker_port = rocker_port;
	switchdev_work->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE: /* fall through */
	case SWITCHDEV_FDB_DEL_TO_DEVICE:
		memcpy(&switchdev_work->fdb_info, ptr,
		       sizeof(switchdev_work->fdb_info));
		switchdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		if (unlikely(!switchdev_work->fdb_info.addr)) {
			kfree(switchdev_work);
			return NOTIFY_BAD;
		}

		ether_addr_copy((u8 *)switchdev_work->fdb_info.addr,
				fdb_info->addr);
		/* Take a reference on the rocker device */
		dev_hold(dev);
		break;
	default:
		kfree(switchdev_work);
		return NOTIFY_DONE;
	}

	queue_work(rocker_port->rocker->rocker_owq,
		   &switchdev_work->work);
	return NOTIFY_DONE;
}