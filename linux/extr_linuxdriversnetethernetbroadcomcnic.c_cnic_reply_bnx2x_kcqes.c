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
typedef  int /*<<< orphan*/  u32 ;
struct kcqe {int dummy; } ;
struct cnic_ulp_ops {int /*<<< orphan*/  (* indicate_kcqes ) (int /*<<< orphan*/ ,struct kcqe**,int /*<<< orphan*/ ) ;} ;
struct cnic_local {int /*<<< orphan*/ * ulp_handle; int /*<<< orphan*/ * ulp_ops; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 scalar_t__ likely (struct cnic_ulp_ops*) ; 
 struct cnic_ulp_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct kcqe**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_reply_bnx2x_kcqes(struct cnic_dev *dev, int ulp_type,
				   struct kcqe *cqes[], u32 num_cqes)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_ulp_ops *ulp_ops;

	rcu_read_lock();
	ulp_ops = rcu_dereference(cp->ulp_ops[ulp_type]);
	if (likely(ulp_ops)) {
		ulp_ops->indicate_kcqes(cp->ulp_handle[ulp_type],
					  cqes, num_cqes);
	}
	rcu_read_unlock();
}