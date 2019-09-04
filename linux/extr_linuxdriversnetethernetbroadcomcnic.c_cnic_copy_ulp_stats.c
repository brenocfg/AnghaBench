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
struct cnic_ulp_ops {int (* cnic_get_stats ) (int /*<<< orphan*/ ) ;} ;
struct cnic_local {int /*<<< orphan*/ * ulp_handle; int /*<<< orphan*/ * ulp_ops; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cnic_lock ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cnic_ulp_ops* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_copy_ulp_stats(struct cnic_dev *dev, int ulp_type)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_ulp_ops *ulp_ops;
	int rc;

	mutex_lock(&cnic_lock);
	ulp_ops = rcu_dereference_protected(cp->ulp_ops[ulp_type],
					    lockdep_is_held(&cnic_lock));
	if (ulp_ops && ulp_ops->cnic_get_stats)
		rc = ulp_ops->cnic_get_stats(cp->ulp_handle[ulp_type]);
	else
		rc = -ENODEV;
	mutex_unlock(&cnic_lock);
	return rc;
}