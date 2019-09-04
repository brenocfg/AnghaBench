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
typedef  int uint32_t ;
struct ttm_object_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_REF_SYNCCPU_WRITE ; 
 int drm_vmw_synccpu_allow_cs ; 
 int ttm_ref_object_base_unref (struct ttm_object_file*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_user_bo_synccpu_release(uint32_t handle,
					   struct ttm_object_file *tfile,
					   uint32_t flags)
{
	if (!(flags & drm_vmw_synccpu_allow_cs))
		return ttm_ref_object_base_unref(tfile, handle,
						 TTM_REF_SYNCCPU_WRITE);

	return 0;
}