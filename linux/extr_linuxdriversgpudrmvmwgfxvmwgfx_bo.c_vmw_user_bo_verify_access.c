#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct vmw_user_buffer_object {TYPE_1__ prime; } ;
struct ttm_object_file {int dummy; } ;
struct ttm_buffer_object {scalar_t__ destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EPERM ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_ref_object_exists (struct ttm_object_file*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vmw_user_bo_destroy ; 
 struct vmw_user_buffer_object* vmw_user_buffer_object (struct ttm_buffer_object*) ; 

int vmw_user_bo_verify_access(struct ttm_buffer_object *bo,
			      struct ttm_object_file *tfile)
{
	struct vmw_user_buffer_object *vmw_user_bo;

	if (unlikely(bo->destroy != vmw_user_bo_destroy))
		return -EPERM;

	vmw_user_bo = vmw_user_buffer_object(bo);

	/* Check that the caller has opened the object. */
	if (likely(ttm_ref_object_exists(tfile, &vmw_user_bo->prime.base)))
		return 0;

	DRM_ERROR("Could not grant buffer access.\n");
	return -EPERM;
}