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
typedef  unsigned int u16 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char const*,int,...) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int ilk_wm_max_level (struct drm_i915_private*) ; 

__attribute__((used)) static void intel_print_wm_latency(struct drm_i915_private *dev_priv,
				   const char *name,
				   const u16 wm[8])
{
	int level, max_level = ilk_wm_max_level(dev_priv);

	for (level = 0; level <= max_level; level++) {
		unsigned int latency = wm[level];

		if (latency == 0) {
			DRM_DEBUG_KMS("%s WM%d latency not provided\n",
				      name, level);
			continue;
		}

		/*
		 * - latencies are in us on gen9.
		 * - before then, WM1+ latency values are in 0.5us units
		 */
		if (INTEL_GEN(dev_priv) >= 9)
			latency *= 10;
		else if (level > 0)
			latency *= 5;

		DRM_DEBUG_KMS("%s WM%d latency %u (%u.%u usec)\n",
			      name, level, wm[level],
			      latency / 10, latency % 10);
	}
}