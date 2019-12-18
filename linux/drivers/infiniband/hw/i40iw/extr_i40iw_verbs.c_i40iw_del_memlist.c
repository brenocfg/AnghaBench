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
struct i40iw_ucontext {int /*<<< orphan*/  qp_reg_mem_list_lock; int /*<<< orphan*/  cq_reg_mem_list_lock; } ;
struct i40iw_pbl {int on_list; int /*<<< orphan*/  list; } ;
struct i40iw_mr {int type; struct i40iw_pbl iwpbl; } ;

/* Variables and functions */
#define  IW_MEMREG_TYPE_CQ 129 
#define  IW_MEMREG_TYPE_QP 128 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void i40iw_del_memlist(struct i40iw_mr *iwmr,
			      struct i40iw_ucontext *ucontext)
{
	struct i40iw_pbl *iwpbl = &iwmr->iwpbl;
	unsigned long flags;

	switch (iwmr->type) {
	case IW_MEMREG_TYPE_CQ:
		spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
		if (iwpbl->on_list) {
			iwpbl->on_list = false;
			list_del(&iwpbl->list);
		}
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		break;
	case IW_MEMREG_TYPE_QP:
		spin_lock_irqsave(&ucontext->qp_reg_mem_list_lock, flags);
		if (iwpbl->on_list) {
			iwpbl->on_list = false;
			list_del(&iwpbl->list);
		}
		spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);
		break;
	default:
		break;
	}
}