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
struct vmw_validation_context {scalar_t__ res_mutex; } ;
struct vmw_fence_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (scalar_t__) ; 
 int /*<<< orphan*/  vmw_validation_bo_fence (struct vmw_validation_context*,struct vmw_fence_obj*) ; 
 int /*<<< orphan*/  vmw_validation_res_unreserve (struct vmw_validation_context*,int) ; 
 int /*<<< orphan*/  vmw_validation_unref_lists (struct vmw_validation_context*) ; 

void vmw_validation_done(struct vmw_validation_context *ctx,
			 struct vmw_fence_obj *fence)
{
	vmw_validation_bo_fence(ctx, fence);
	vmw_validation_res_unreserve(ctx, false);
	if (ctx->res_mutex)
		mutex_unlock(ctx->res_mutex);
	vmw_validation_unref_lists(ctx);
}