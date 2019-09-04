#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  has_guc; } ;
struct TYPE_9__ {void* path; } ;
struct TYPE_8__ {void* path; } ;
struct i915_error_uc {int /*<<< orphan*/  guc_log; TYPE_3__ huc_fw; TYPE_2__ guc_fw; } ;
struct i915_gpu_state {TYPE_1__ device_info; struct i915_error_uc uc; struct drm_i915_private* i915; } ;
struct TYPE_11__ {int /*<<< orphan*/  vma; } ;
struct TYPE_12__ {TYPE_5__ log; TYPE_2__ fw; } ;
struct TYPE_10__ {TYPE_3__ fw; } ;
struct drm_i915_private {TYPE_6__ guc; TYPE_4__ huc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  i915_error_object_create (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 void* kstrdup (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void capture_uc_state(struct i915_gpu_state *error)
{
	struct drm_i915_private *i915 = error->i915;
	struct i915_error_uc *error_uc = &error->uc;

	/* Capturing uC state won't be useful if there is no GuC */
	if (!error->device_info.has_guc)
		return;

	error_uc->guc_fw = i915->guc.fw;
	error_uc->huc_fw = i915->huc.fw;

	/* Non-default firmware paths will be specified by the modparam.
	 * As modparams are generally accesible from the userspace make
	 * explicit copies of the firmware paths.
	 */
	error_uc->guc_fw.path = kstrdup(i915->guc.fw.path, GFP_ATOMIC);
	error_uc->huc_fw.path = kstrdup(i915->huc.fw.path, GFP_ATOMIC);
	error_uc->guc_log = i915_error_object_create(i915, i915->guc.log.vma);
}