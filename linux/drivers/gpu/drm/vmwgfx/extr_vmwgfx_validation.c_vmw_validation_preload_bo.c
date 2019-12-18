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
struct vmw_validation_context {unsigned int mem_size_left; } ;
struct vmw_validation_bo_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  vmw_validation_mem_alloc (struct vmw_validation_context*,unsigned int) ; 

int vmw_validation_preload_bo(struct vmw_validation_context *ctx)
{
	unsigned int size = sizeof(struct vmw_validation_bo_node);

	if (!vmw_validation_mem_alloc(ctx, size))
		return -ENOMEM;

	ctx->mem_size_left += size;
	return 0;
}