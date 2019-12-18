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
struct intel_runtime_info {int /*<<< orphan*/  sseu; } ;
struct intel_driver_caps {int dummy; } ;
struct intel_device_info {int dummy; } ;
struct drm_printer {int dummy; } ;
struct drm_i915_error_state_buf {int dummy; } ;

/* Variables and functions */
 struct drm_printer i915_error_printer (struct drm_i915_error_state_buf*) ; 
 int /*<<< orphan*/  intel_device_info_dump_flags (struct intel_device_info const*,struct drm_printer*) ; 
 int /*<<< orphan*/  intel_device_info_dump_topology (int /*<<< orphan*/ *,struct drm_printer*) ; 
 int /*<<< orphan*/  intel_driver_caps_print (struct intel_driver_caps const*,struct drm_printer*) ; 

__attribute__((used)) static void err_print_capabilities(struct drm_i915_error_state_buf *m,
				   const struct intel_device_info *info,
				   const struct intel_runtime_info *runtime,
				   const struct intel_driver_caps *caps)
{
	struct drm_printer p = i915_error_printer(m);

	intel_device_info_dump_flags(info, &p);
	intel_driver_caps_print(caps, &p);
	intel_device_info_dump_topology(&runtime->sseu, &p);
}