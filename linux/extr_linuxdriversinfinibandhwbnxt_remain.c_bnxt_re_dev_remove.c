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
struct bnxt_re_dev {int /*<<< orphan*/  ibdev; int /*<<< orphan*/  list; int /*<<< orphan*/ * netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_re_dev_lock ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void bnxt_re_dev_remove(struct bnxt_re_dev *rdev)
{
	dev_put(rdev->netdev);
	rdev->netdev = NULL;

	mutex_lock(&bnxt_re_dev_lock);
	list_del_rcu(&rdev->list);
	mutex_unlock(&bnxt_re_dev_lock);

	synchronize_rcu();

	ib_dealloc_device(&rdev->ibdev);
	/* rdev is gone */
}