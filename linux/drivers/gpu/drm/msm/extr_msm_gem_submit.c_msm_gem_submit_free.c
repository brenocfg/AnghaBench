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
struct msm_gem_submit {int /*<<< orphan*/  queue; int /*<<< orphan*/  pid; int /*<<< orphan*/  node; int /*<<< orphan*/  fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msm_gem_submit*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_submitqueue_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 

void msm_gem_submit_free(struct msm_gem_submit *submit)
{
	dma_fence_put(submit->fence);
	list_del(&submit->node);
	put_pid(submit->pid);
	msm_submitqueue_put(submit->queue);

	kfree(submit);
}