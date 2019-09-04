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
struct ib_ucontext {int dummy; } ;
struct i40iw_ucontext {int /*<<< orphan*/  qp_reg_mem_list_lock; int /*<<< orphan*/  qp_reg_mem_list; int /*<<< orphan*/  cq_reg_mem_list_lock; int /*<<< orphan*/  cq_reg_mem_list; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  kfree (struct i40iw_ucontext*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i40iw_ucontext* to_ucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int i40iw_dealloc_ucontext(struct ib_ucontext *context)
{
	struct i40iw_ucontext *ucontext = to_ucontext(context);
	unsigned long flags;

	spin_lock_irqsave(&ucontext->cq_reg_mem_list_lock, flags);
	if (!list_empty(&ucontext->cq_reg_mem_list)) {
		spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
		return -EBUSY;
	}
	spin_unlock_irqrestore(&ucontext->cq_reg_mem_list_lock, flags);
	spin_lock_irqsave(&ucontext->qp_reg_mem_list_lock, flags);
	if (!list_empty(&ucontext->qp_reg_mem_list)) {
		spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);
		return -EBUSY;
	}
	spin_unlock_irqrestore(&ucontext->qp_reg_mem_list_lock, flags);

	kfree(ucontext);
	return 0;
}