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
struct vmw_fence_obj {int dummy; } ;
struct vmw_fence_manager {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct vmw_fence_obj*) ; 
 struct vmw_fence_obj* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_fence_destroy ; 
 int vmw_fence_obj_init (struct vmw_fence_manager*,struct vmw_fence_obj*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vmw_fence_create(struct vmw_fence_manager *fman,
		     uint32_t seqno,
		     struct vmw_fence_obj **p_fence)
{
	struct vmw_fence_obj *fence;
 	int ret;

	fence = kzalloc(sizeof(*fence), GFP_KERNEL);
	if (unlikely(!fence))
		return -ENOMEM;

	ret = vmw_fence_obj_init(fman, fence, seqno,
				 vmw_fence_destroy);
	if (unlikely(ret != 0))
		goto out_err_init;

	*p_fence = fence;
	return 0;

out_err_init:
	kfree(fence);
	return ret;
}