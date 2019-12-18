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
struct cnic_ulp_ops {int /*<<< orphan*/  (* cnic_init ) (struct cnic_dev*) ;} ;
struct cnic_local {int /*<<< orphan*/ * ulp_flags; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 int MAX_CNIC_ULP_TYPE_EXT ; 
 int /*<<< orphan*/  ULP_F_INIT ; 
 int /*<<< orphan*/  cnic_lock ; 
 struct cnic_ulp_ops* cnic_ulp_tbl_prot (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cnic_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulp_get (struct cnic_ulp_ops*) ; 
 int /*<<< orphan*/  ulp_put (struct cnic_ulp_ops*) ; 

__attribute__((used)) static void cnic_ulp_init(struct cnic_dev *dev)
{
	int i;
	struct cnic_local *cp = dev->cnic_priv;

	for (i = 0; i < MAX_CNIC_ULP_TYPE_EXT; i++) {
		struct cnic_ulp_ops *ulp_ops;

		mutex_lock(&cnic_lock);
		ulp_ops = cnic_ulp_tbl_prot(i);
		if (!ulp_ops || !ulp_ops->cnic_init) {
			mutex_unlock(&cnic_lock);
			continue;
		}
		ulp_get(ulp_ops);
		mutex_unlock(&cnic_lock);

		if (!test_and_set_bit(ULP_F_INIT, &cp->ulp_flags[i]))
			ulp_ops->cnic_init(dev);

		ulp_put(ulp_ops);
	}
}