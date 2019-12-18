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
struct ttm_object_file {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct file {scalar_t__ private_data; } ;
struct drm_file {int dummy; } ;
struct TYPE_2__ {struct ttm_object_file* tfile; } ;

/* Variables and functions */
 TYPE_1__* vmw_fpriv (struct drm_file*) ; 
 int vmw_user_bo_verify_access (struct ttm_buffer_object*,struct ttm_object_file*) ; 

__attribute__((used)) static int vmw_verify_access(struct ttm_buffer_object *bo, struct file *filp)
{
	struct ttm_object_file *tfile =
		vmw_fpriv((struct drm_file *)filp->private_data)->tfile;

	return vmw_user_bo_verify_access(bo, tfile);
}