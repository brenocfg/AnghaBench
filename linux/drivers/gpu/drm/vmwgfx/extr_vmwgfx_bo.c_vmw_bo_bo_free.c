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
struct vmw_buffer_object {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_buffer_object*) ; 
 int /*<<< orphan*/  vmw_bo_unmap (struct vmw_buffer_object*) ; 
 struct vmw_buffer_object* vmw_buffer_object (struct ttm_buffer_object*) ; 

void vmw_bo_bo_free(struct ttm_buffer_object *bo)
{
	struct vmw_buffer_object *vmw_bo = vmw_buffer_object(bo);

	vmw_bo_unmap(vmw_bo);
	kfree(vmw_bo);
}