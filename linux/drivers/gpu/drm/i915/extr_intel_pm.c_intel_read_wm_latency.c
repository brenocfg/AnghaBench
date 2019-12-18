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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct intel_uncore {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_16gb_dimm; } ;
struct drm_i915_private {TYPE_1__ dram_info; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT ; 
 scalar_t__ GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT ; 
 scalar_t__ GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT ; 
 scalar_t__ GEN9_MEM_LATENCY_LEVEL_MASK ; 
 int /*<<< orphan*/  GEN9_PCODE_READ_MEM_LATENCY ; 
 scalar_t__ ILK_SRLT_MASK ; 
 int /*<<< orphan*/  INTEL_DEVID (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  MCH_SSKPD ; 
 int /*<<< orphan*/  MISSING_CASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLTR_ILK ; 
 scalar_t__ MLTR_WM1_SHIFT ; 
 scalar_t__ MLTR_WM2_SHIFT ; 
 scalar_t__ SSKPD_WM0_SHIFT ; 
 scalar_t__ SSKPD_WM1_SHIFT ; 
 scalar_t__ SSKPD_WM2_SHIFT ; 
 scalar_t__ SSKPD_WM3_SHIFT ; 
 scalar_t__ SSKPD_WM_MASK ; 
 int ilk_wm_max_level (struct drm_i915_private*) ; 
 scalar_t__ intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read64 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int sandybridge_pcode_read (struct drm_i915_private*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_read_wm_latency(struct drm_i915_private *dev_priv,
				  u16 wm[8])
{
	struct intel_uncore *uncore = &dev_priv->uncore;

	if (INTEL_GEN(dev_priv) >= 9) {
		u32 val;
		int ret, i;
		int level, max_level = ilk_wm_max_level(dev_priv);

		/* read the first set of memory latencies[0:3] */
		val = 0; /* data0 to be programmed to 0 for first set */
		ret = sandybridge_pcode_read(dev_priv,
					     GEN9_PCODE_READ_MEM_LATENCY,
					     &val, NULL);

		if (ret) {
			DRM_ERROR("SKL Mailbox read error = %d\n", ret);
			return;
		}

		wm[0] = val & GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[1] = (val >> GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[2] = (val >> GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[3] = (val >> GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;

		/* read the second set of memory latencies[4:7] */
		val = 1; /* data0 to be programmed to 1 for second set */
		ret = sandybridge_pcode_read(dev_priv,
					     GEN9_PCODE_READ_MEM_LATENCY,
					     &val, NULL);
		if (ret) {
			DRM_ERROR("SKL Mailbox read error = %d\n", ret);
			return;
		}

		wm[4] = val & GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[5] = (val >> GEN9_MEM_LATENCY_LEVEL_1_5_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[6] = (val >> GEN9_MEM_LATENCY_LEVEL_2_6_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;
		wm[7] = (val >> GEN9_MEM_LATENCY_LEVEL_3_7_SHIFT) &
				GEN9_MEM_LATENCY_LEVEL_MASK;

		/*
		 * If a level n (n > 1) has a 0us latency, all levels m (m >= n)
		 * need to be disabled. We make sure to sanitize the values out
		 * of the punit to satisfy this requirement.
		 */
		for (level = 1; level <= max_level; level++) {
			if (wm[level] == 0) {
				for (i = level + 1; i <= max_level; i++)
					wm[i] = 0;
				break;
			}
		}

		/*
		 * WaWmMemoryReadLatency:skl+,glk
		 *
		 * punit doesn't take into account the read latency so we need
		 * to add 2us to the various latency levels we retrieve from the
		 * punit when level 0 response data us 0us.
		 */
		if (wm[0] == 0) {
			wm[0] += 2;
			for (level = 1; level <= max_level; level++) {
				if (wm[level] == 0)
					break;
				wm[level] += 2;
			}
		}

		/*
		 * WA Level-0 adjustment for 16GB DIMMs: SKL+
		 * If we could not get dimm info enable this WA to prevent from
		 * any underrun. If not able to get Dimm info assume 16GB dimm
		 * to avoid any underrun.
		 */
		if (dev_priv->dram_info.is_16gb_dimm)
			wm[0] += 1;

	} else if (IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv)) {
		u64 sskpd = intel_uncore_read64(uncore, MCH_SSKPD);

		wm[0] = (sskpd >> 56) & 0xFF;
		if (wm[0] == 0)
			wm[0] = sskpd & 0xF;
		wm[1] = (sskpd >> 4) & 0xFF;
		wm[2] = (sskpd >> 12) & 0xFF;
		wm[3] = (sskpd >> 20) & 0x1FF;
		wm[4] = (sskpd >> 32) & 0x1FF;
	} else if (INTEL_GEN(dev_priv) >= 6) {
		u32 sskpd = intel_uncore_read(uncore, MCH_SSKPD);

		wm[0] = (sskpd >> SSKPD_WM0_SHIFT) & SSKPD_WM_MASK;
		wm[1] = (sskpd >> SSKPD_WM1_SHIFT) & SSKPD_WM_MASK;
		wm[2] = (sskpd >> SSKPD_WM2_SHIFT) & SSKPD_WM_MASK;
		wm[3] = (sskpd >> SSKPD_WM3_SHIFT) & SSKPD_WM_MASK;
	} else if (INTEL_GEN(dev_priv) >= 5) {
		u32 mltr = intel_uncore_read(uncore, MLTR_ILK);

		/* ILK primary LP0 latency is 700 ns */
		wm[0] = 7;
		wm[1] = (mltr >> MLTR_WM1_SHIFT) & ILK_SRLT_MASK;
		wm[2] = (mltr >> MLTR_WM2_SHIFT) & ILK_SRLT_MASK;
	} else {
		MISSING_CASE(INTEL_DEVID(dev_priv));
	}
}