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
typedef  int /*<<< orphan*/  u16 ;
struct cnic_ulp_ops {int /*<<< orphan*/  (* indicate_netevent ) (void*,unsigned long,int /*<<< orphan*/ ) ;} ;
struct cnic_local {int /*<<< orphan*/ * ulp_flags; void** ulp_handle; int /*<<< orphan*/ * ulp_ops; } ;

/* Variables and functions */
 int MAX_CNIC_ULP_TYPE ; 
 int /*<<< orphan*/  ULP_F_CALL_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cnic_lock ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cnic_ulp_ops* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (void*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_rcv_netevent(struct cnic_local *cp, unsigned long event,
			      u16 vlan_id)
{
	int if_type;

	for (if_type = 0; if_type < MAX_CNIC_ULP_TYPE; if_type++) {
		struct cnic_ulp_ops *ulp_ops;
		void *ctx;

		mutex_lock(&cnic_lock);
		ulp_ops = rcu_dereference_protected(cp->ulp_ops[if_type],
						lockdep_is_held(&cnic_lock));
		if (!ulp_ops || !ulp_ops->indicate_netevent) {
			mutex_unlock(&cnic_lock);
			continue;
		}

		ctx = cp->ulp_handle[if_type];

		set_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[if_type]);
		mutex_unlock(&cnic_lock);

		ulp_ops->indicate_netevent(ctx, event, vlan_id);

		clear_bit(ULP_F_CALL_PENDING, &cp->ulp_flags[if_type]);
	}
}