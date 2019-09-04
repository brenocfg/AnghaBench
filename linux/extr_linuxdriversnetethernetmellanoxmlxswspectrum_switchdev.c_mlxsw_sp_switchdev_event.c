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
typedef  int /*<<< orphan*/  u8 ;
struct switchdev_notifier_fdb_info {int /*<<< orphan*/  addr; } ;
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {void* addr; } ;
struct mlxsw_sp_switchdev_event_work {unsigned long event; int /*<<< orphan*/  work; TYPE_1__ fdb_info; struct net_device* dev; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
#define  SWITCHDEV_FDB_ADD_TO_BRIDGE 131 
#define  SWITCHDEV_FDB_ADD_TO_DEVICE 130 
#define  SWITCHDEV_FDB_DEL_TO_BRIDGE 129 
#define  SWITCHDEV_FDB_DEL_TO_DEVICE 128 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_switchdev_event_work*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,void*,int) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_port_dev_lower_find_rcu (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_event_work ; 
 struct net_device* switchdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int mlxsw_sp_switchdev_event(struct notifier_block *unused,
				    unsigned long event, void *ptr)
{
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	struct mlxsw_sp_switchdev_event_work *switchdev_work;
	struct switchdev_notifier_fdb_info *fdb_info = ptr;

	if (!mlxsw_sp_port_dev_lower_find_rcu(dev))
		return NOTIFY_DONE;

	switchdev_work = kzalloc(sizeof(*switchdev_work), GFP_ATOMIC);
	if (!switchdev_work)
		return NOTIFY_BAD;

	INIT_WORK(&switchdev_work->work, mlxsw_sp_switchdev_event_work);
	switchdev_work->dev = dev;
	switchdev_work->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE: /* fall through */
	case SWITCHDEV_FDB_DEL_TO_DEVICE: /* fall through */
	case SWITCHDEV_FDB_ADD_TO_BRIDGE: /* fall through */
	case SWITCHDEV_FDB_DEL_TO_BRIDGE:
		memcpy(&switchdev_work->fdb_info, ptr,
		       sizeof(switchdev_work->fdb_info));
		switchdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		if (!switchdev_work->fdb_info.addr)
			goto err_addr_alloc;
		ether_addr_copy((u8 *)switchdev_work->fdb_info.addr,
				fdb_info->addr);
		/* Take a reference on the device. This can be either
		 * upper device containig mlxsw_sp_port or just a
		 * mlxsw_sp_port
		 */
		dev_hold(dev);
		break;
	default:
		kfree(switchdev_work);
		return NOTIFY_DONE;
	}

	mlxsw_core_schedule_work(&switchdev_work->work);

	return NOTIFY_DONE;

err_addr_alloc:
	kfree(switchdev_work);
	return NOTIFY_BAD;
}