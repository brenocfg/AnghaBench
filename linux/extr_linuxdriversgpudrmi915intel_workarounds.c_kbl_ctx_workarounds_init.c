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
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMON_SLICE_CHICKEN2 ; 
 int /*<<< orphan*/  GEN7_HALF_SLICE_CHICKEN1 ; 
 int /*<<< orphan*/  GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE ; 
 int /*<<< orphan*/  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION ; 
 int /*<<< orphan*/  HDC_CHICKEN0 ; 
 int /*<<< orphan*/  HDC_FENCE_DEST_SLM_DISABLE ; 
 scalar_t__ IS_KBL_REVID (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBL_REVID_A0 ; 
 int /*<<< orphan*/  KBL_REVID_C0 ; 
 int /*<<< orphan*/  REVID_FOREVER ; 
 int /*<<< orphan*/  WA_SET_BIT_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gen9_ctx_workarounds_init (struct drm_i915_private*) ; 

__attribute__((used)) static int kbl_ctx_workarounds_init(struct drm_i915_private *dev_priv)
{
	int ret;

	ret = gen9_ctx_workarounds_init(dev_priv);
	if (ret)
		return ret;

	/* WaDisableFenceDestinationToSLM:kbl (pre-prod) */
	if (IS_KBL_REVID(dev_priv, KBL_REVID_A0, KBL_REVID_A0))
		WA_SET_BIT_MASKED(HDC_CHICKEN0,
				  HDC_FENCE_DEST_SLM_DISABLE);

	/* WaToEnableHwFixForPushConstHWBug:kbl */
	if (IS_KBL_REVID(dev_priv, KBL_REVID_C0, REVID_FOREVER))
		WA_SET_BIT_MASKED(COMMON_SLICE_CHICKEN2,
				  GEN8_SBE_DISABLE_REPLAY_BUF_OPTIMIZATION);

	/* WaDisableSbeCacheDispatchPortSharing:kbl */
	WA_SET_BIT_MASKED(GEN7_HALF_SLICE_CHICKEN1,
			  GEN7_SBE_SS_CACHE_DISPATCH_PORT_SHARING_DISABLE);

	return 0;
}