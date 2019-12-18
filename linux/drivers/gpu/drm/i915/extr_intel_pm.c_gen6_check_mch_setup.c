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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCH_SSKPD ; 
 int MCH_SSKPD_WM0_MASK ; 
 int MCH_SSKPD_WM0_VAL ; 

__attribute__((used)) static void gen6_check_mch_setup(struct drm_i915_private *dev_priv)
{
	u32 tmp;

	tmp = I915_READ(MCH_SSKPD);
	if ((tmp & MCH_SSKPD_WM0_MASK) != MCH_SSKPD_WM0_VAL)
		DRM_DEBUG_KMS("Wrong MCH_SSKPD value: 0x%08x This can cause underruns.\n",
			      tmp);
}