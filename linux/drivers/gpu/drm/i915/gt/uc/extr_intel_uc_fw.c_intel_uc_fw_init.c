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
struct intel_uc_fw {int /*<<< orphan*/  type; int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int) ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_FAIL ; 
 int i915_gem_object_pin_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_change_status (struct intel_uc_fw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (struct intel_uc_fw*) ; 
 int /*<<< orphan*/  intel_uc_fw_is_loaded (struct intel_uc_fw*) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int /*<<< orphan*/ ) ; 

int intel_uc_fw_init(struct intel_uc_fw *uc_fw)
{
	int err;

	/* this should happen before the load! */
	GEM_BUG_ON(intel_uc_fw_is_loaded(uc_fw));

	if (!intel_uc_fw_is_available(uc_fw))
		return -ENOEXEC;

	err = i915_gem_object_pin_pages(uc_fw->obj);
	if (err) {
		DRM_DEBUG_DRIVER("%s fw pin-pages err=%d\n",
				 intel_uc_fw_type_repr(uc_fw->type), err);
		intel_uc_fw_change_status(uc_fw, INTEL_UC_FIRMWARE_FAIL);
	}

	return err;
}