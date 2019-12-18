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
struct intel_rps_ei {void* media_c0; void* render_c0; int /*<<< orphan*/  ktime; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 void* I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLV_MEDIA_C0_COUNT ; 
 int /*<<< orphan*/  VLV_RENDER_C0_COUNT ; 
 int /*<<< orphan*/  ktime_get_raw () ; 

__attribute__((used)) static void vlv_c0_read(struct drm_i915_private *dev_priv,
			struct intel_rps_ei *ei)
{
	ei->ktime = ktime_get_raw();
	ei->render_c0 = I915_READ(VLV_RENDER_C0_COUNT);
	ei->media_c0 = I915_READ(VLV_MEDIA_C0_COUNT);
}