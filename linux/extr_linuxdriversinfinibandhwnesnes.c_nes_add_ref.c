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
struct nes_qp {int /*<<< orphan*/  refcount; } ;
struct ib_qp {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_DBG_QP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 

void nes_add_ref(struct ib_qp *ibqp)
{
	struct nes_qp *nesqp;

	nesqp = to_nesqp(ibqp);
	nes_debug(NES_DBG_QP, "Bumping refcount for QP%u.  Pre-inc value = %u\n",
			ibqp->qp_num, atomic_read(&nesqp->refcount));
	atomic_inc(&nesqp->refcount);
}