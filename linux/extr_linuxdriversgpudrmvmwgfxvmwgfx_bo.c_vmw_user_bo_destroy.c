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
struct vmw_user_buffer_object {int /*<<< orphan*/  vbo; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prime ; 
 int /*<<< orphan*/  ttm_prime_object_kfree (struct vmw_user_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_unmap (int /*<<< orphan*/ *) ; 
 struct vmw_user_buffer_object* vmw_user_buffer_object (struct ttm_buffer_object*) ; 

__attribute__((used)) static void vmw_user_bo_destroy(struct ttm_buffer_object *bo)
{
	struct vmw_user_buffer_object *vmw_user_bo = vmw_user_buffer_object(bo);

	vmw_bo_unmap(&vmw_user_bo->vbo);
	ttm_prime_object_kfree(vmw_user_bo, prime);
}