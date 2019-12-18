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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct bnxt_re_work {unsigned long event; int /*<<< orphan*/  work; struct net_device* vlan_dev; struct bnxt_re_dev* rdev; } ;
struct bnxt_re_dev {int /*<<< orphan*/  sched_count; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int bnxt_re_dev_reg (struct bnxt_re_dev**,struct net_device*) ; 
 int /*<<< orphan*/  bnxt_re_dev_unreg (struct bnxt_re_dev*) ; 
 struct bnxt_re_dev* bnxt_re_from_netdev (struct net_device*) ; 
 int /*<<< orphan*/  bnxt_re_ib_unreg (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_init_one (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_remove_one (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_task ; 
 int /*<<< orphan*/  bnxt_re_wq ; 
 struct bnxt_re_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* rdma_vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static int bnxt_re_netdev_event(struct notifier_block *notifier,
				unsigned long event, void *ptr)
{
	struct net_device *real_dev, *netdev = netdev_notifier_info_to_dev(ptr);
	struct bnxt_re_work *re_work;
	struct bnxt_re_dev *rdev;
	int rc = 0;
	bool sch_work = false;

	real_dev = rdma_vlan_dev_real_dev(netdev);
	if (!real_dev)
		real_dev = netdev;

	rdev = bnxt_re_from_netdev(real_dev);
	if (!rdev && event != NETDEV_REGISTER)
		goto exit;
	if (real_dev != netdev)
		goto exit;

	switch (event) {
	case NETDEV_REGISTER:
		if (rdev)
			break;
		rc = bnxt_re_dev_reg(&rdev, real_dev);
		if (rc == -ENODEV)
			break;
		if (rc) {
			pr_err("Failed to register with the device %s: %#x\n",
			       real_dev->name, rc);
			break;
		}
		bnxt_re_init_one(rdev);
		sch_work = true;
		break;

	case NETDEV_UNREGISTER:
		/* netdev notifier will call NETDEV_UNREGISTER again later since
		 * we are still holding the reference to the netdev
		 */
		if (atomic_read(&rdev->sched_count) > 0)
			goto exit;
		bnxt_re_ib_unreg(rdev);
		bnxt_re_remove_one(rdev);
		bnxt_re_dev_unreg(rdev);
		break;

	default:
		sch_work = true;
		break;
	}
	if (sch_work) {
		/* Allocate for the deferred task */
		re_work = kzalloc(sizeof(*re_work), GFP_ATOMIC);
		if (re_work) {
			re_work->rdev = rdev;
			re_work->event = event;
			re_work->vlan_dev = (real_dev == netdev ?
					     NULL : netdev);
			INIT_WORK(&re_work->work, bnxt_re_task);
			atomic_inc(&rdev->sched_count);
			queue_work(bnxt_re_wq, &re_work->work);
		}
	}

exit:
	return NOTIFY_DONE;
}