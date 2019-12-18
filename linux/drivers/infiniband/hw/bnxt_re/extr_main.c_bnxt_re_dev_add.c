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
struct net_device {int dummy; } ;
struct bnxt_re_dev {int* cosq; int /*<<< orphan*/  list; int /*<<< orphan*/  mw_count; int /*<<< orphan*/  mr_count; int /*<<< orphan*/  srq_count; int /*<<< orphan*/  cq_count; int /*<<< orphan*/  qp_count; int /*<<< orphan*/  qp_lock; int /*<<< orphan*/  qp_list; struct bnxt_en_dev* en_dev; int /*<<< orphan*/  id; struct net_device* netdev; } ;
struct bnxt_en_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ROCE_DRV_MODULE_NAME ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_re_dev ; 
 int /*<<< orphan*/  bnxt_re_dev_list ; 
 int /*<<< orphan*/  bnxt_re_dev_lock ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 struct bnxt_re_dev* ib_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibdev ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct bnxt_re_dev *bnxt_re_dev_add(struct net_device *netdev,
					   struct bnxt_en_dev *en_dev)
{
	struct bnxt_re_dev *rdev;

	/* Allocate bnxt_re_dev instance here */
	rdev = ib_alloc_device(bnxt_re_dev, ibdev);
	if (!rdev) {
		dev_err(NULL, "%s: bnxt_re_dev allocation failure!",
			ROCE_DRV_MODULE_NAME);
		return NULL;
	}
	/* Default values */
	rdev->netdev = netdev;
	dev_hold(rdev->netdev);
	rdev->en_dev = en_dev;
	rdev->id = rdev->en_dev->pdev->devfn;
	INIT_LIST_HEAD(&rdev->qp_list);
	mutex_init(&rdev->qp_lock);
	atomic_set(&rdev->qp_count, 0);
	atomic_set(&rdev->cq_count, 0);
	atomic_set(&rdev->srq_count, 0);
	atomic_set(&rdev->mr_count, 0);
	atomic_set(&rdev->mw_count, 0);
	rdev->cosq[0] = 0xFFFF;
	rdev->cosq[1] = 0xFFFF;

	mutex_lock(&bnxt_re_dev_lock);
	list_add_tail_rcu(&rdev->list, &bnxt_re_dev_list);
	mutex_unlock(&bnxt_re_dev_lock);
	return rdev;
}