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
typedef  scalar_t__ u8 ;
struct cnic_ulp_ops {int /*<<< orphan*/  (* cm_remote_close ) (struct cnic_sock*) ;int /*<<< orphan*/  (* cm_abort_complete ) (struct cnic_sock*) ;int /*<<< orphan*/  (* cm_remote_abort ) (struct cnic_sock*) ;int /*<<< orphan*/  (* cm_close_complete ) (struct cnic_sock*) ;int /*<<< orphan*/  (* cm_connect_complete ) (struct cnic_sock*) ;} ;
struct cnic_sock {int ulp_type; } ;
struct cnic_local {int /*<<< orphan*/ * ulp_ops; } ;

/* Variables and functions */
 scalar_t__ L4_KCQE_OPCODE_VALUE_CLOSE_COMP ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_COMP ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_RECEIVED ; 
 struct cnic_ulp_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct cnic_sock*) ; 
 int /*<<< orphan*/  stub2 (struct cnic_sock*) ; 
 int /*<<< orphan*/  stub3 (struct cnic_sock*) ; 
 int /*<<< orphan*/  stub4 (struct cnic_sock*) ; 
 int /*<<< orphan*/  stub5 (struct cnic_sock*) ; 

__attribute__((used)) static void cnic_cm_upcall(struct cnic_local *cp, struct cnic_sock *csk,
			   u8 opcode)
{
	struct cnic_ulp_ops *ulp_ops;
	int ulp_type = csk->ulp_type;

	rcu_read_lock();
	ulp_ops = rcu_dereference(cp->ulp_ops[ulp_type]);
	if (ulp_ops) {
		if (opcode == L4_KCQE_OPCODE_VALUE_CONNECT_COMPLETE)
			ulp_ops->cm_connect_complete(csk);
		else if (opcode == L4_KCQE_OPCODE_VALUE_CLOSE_COMP)
			ulp_ops->cm_close_complete(csk);
		else if (opcode == L4_KCQE_OPCODE_VALUE_RESET_RECEIVED)
			ulp_ops->cm_remote_abort(csk);
		else if (opcode == L4_KCQE_OPCODE_VALUE_RESET_COMP)
			ulp_ops->cm_abort_complete(csk);
		else if (opcode == L4_KCQE_OPCODE_VALUE_CLOSE_RECEIVED)
			ulp_ops->cm_remote_close(csk);
	}
	rcu_read_unlock();
}