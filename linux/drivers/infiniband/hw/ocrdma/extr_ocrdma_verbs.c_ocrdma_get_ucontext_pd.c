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
struct ocrdma_ucontext {int pd_in_use; int /*<<< orphan*/  mm_list_lock; struct ocrdma_pd* cntxt_pd; } ;
struct ocrdma_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ocrdma_pd *ocrdma_get_ucontext_pd(struct ocrdma_ucontext *uctx)
{
	struct ocrdma_pd *pd = NULL;

	mutex_lock(&uctx->mm_list_lock);
	if (!uctx->pd_in_use) {
		uctx->pd_in_use = true;
		pd = uctx->cntxt_pd;
	}
	mutex_unlock(&uctx->mm_list_lock);

	return pd;
}