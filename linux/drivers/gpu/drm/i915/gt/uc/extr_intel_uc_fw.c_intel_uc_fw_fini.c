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
struct intel_uc_fw {int /*<<< orphan*/  obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_gem_object_unpin_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_is_available (struct intel_uc_fw*) ; 

void intel_uc_fw_fini(struct intel_uc_fw *uc_fw)
{
	if (!intel_uc_fw_is_available(uc_fw))
		return;

	i915_gem_object_unpin_pages(uc_fw->obj);
}