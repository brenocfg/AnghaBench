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
struct intel_uc_fw {int /*<<< orphan*/  fetch_status; int /*<<< orphan*/  obj; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_NONE ; 
 struct drm_i915_gem_object* fetch_and_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_put (struct drm_i915_gem_object*) ; 

void intel_uc_fw_fini(struct intel_uc_fw *uc_fw)
{
	struct drm_i915_gem_object *obj;

	obj = fetch_and_zero(&uc_fw->obj);
	if (obj)
		i915_gem_object_put(obj);

	uc_fw->fetch_status = INTEL_UC_FIRMWARE_NONE;
}