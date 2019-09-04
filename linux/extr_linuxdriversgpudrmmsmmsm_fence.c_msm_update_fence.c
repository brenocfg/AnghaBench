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
typedef  int /*<<< orphan*/  uint32_t ;
struct msm_fence_context {int /*<<< orphan*/  event; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  completed_fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void msm_update_fence(struct msm_fence_context *fctx, uint32_t fence)
{
	spin_lock(&fctx->spinlock);
	fctx->completed_fence = max(fence, fctx->completed_fence);
	spin_unlock(&fctx->spinlock);

	wake_up_all(&fctx->event);
}