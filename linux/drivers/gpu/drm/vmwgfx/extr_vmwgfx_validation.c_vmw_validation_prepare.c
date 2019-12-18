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
struct vmw_validation_context {struct mutex* res_mutex; } ;
struct mutex {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int mutex_lock_interruptible (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 
 int /*<<< orphan*/  vmw_validation_bo_backoff (struct vmw_validation_context*) ; 
 int vmw_validation_bo_reserve (struct vmw_validation_context*,int) ; 
 int vmw_validation_bo_validate (struct vmw_validation_context*,int) ; 
 int vmw_validation_res_reserve (struct vmw_validation_context*,int) ; 
 int /*<<< orphan*/  vmw_validation_res_unreserve (struct vmw_validation_context*,int) ; 
 int vmw_validation_res_validate (struct vmw_validation_context*,int) ; 

int vmw_validation_prepare(struct vmw_validation_context *ctx,
			   struct mutex *mutex,
			   bool intr)
{
	int ret = 0;

	if (mutex) {
		if (intr)
			ret = mutex_lock_interruptible(mutex);
		else
			mutex_lock(mutex);
		if (ret)
			return -ERESTARTSYS;
	}

	ctx->res_mutex = mutex;
	ret = vmw_validation_res_reserve(ctx, intr);
	if (ret)
		goto out_no_res_reserve;

	ret = vmw_validation_bo_reserve(ctx, intr);
	if (ret)
		goto out_no_bo_reserve;

	ret = vmw_validation_bo_validate(ctx, intr);
	if (ret)
		goto out_no_validate;

	ret = vmw_validation_res_validate(ctx, intr);
	if (ret)
		goto out_no_validate;

	return 0;

out_no_validate:
	vmw_validation_bo_backoff(ctx);
out_no_bo_reserve:
	vmw_validation_res_unreserve(ctx, true);
out_no_res_reserve:
	if (mutex)
		mutex_unlock(mutex);

	return ret;
}