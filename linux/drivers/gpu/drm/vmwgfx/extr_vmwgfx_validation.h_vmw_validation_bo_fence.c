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
struct vmw_validation_context {int /*<<< orphan*/  bo_list; int /*<<< orphan*/  ticket; } ;
struct vmw_fence_obj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_eu_fence_buffer_objects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void
vmw_validation_bo_fence(struct vmw_validation_context *ctx,
			struct vmw_fence_obj *fence)
{
	ttm_eu_fence_buffer_objects(&ctx->ticket, &ctx->bo_list,
				    (void *) fence);
}