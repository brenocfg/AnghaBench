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
typedef  int u32 ;
struct intel_vgpu {TYPE_1__* gvt; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int GAMW_ECO_ENABLE_64K_IPS_FIELD ; 
 int /*<<< orphan*/  GEN8_GAMW_ECO_DEV_RW_IA ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int vgpu_vreg_t (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vgpu_ips_enabled(struct intel_vgpu *vgpu)
{
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;

	if (INTEL_GEN(dev_priv) == 9 || INTEL_GEN(dev_priv) == 10) {
		u32 ips = vgpu_vreg_t(vgpu, GEN8_GAMW_ECO_DEV_RW_IA) &
			GAMW_ECO_ENABLE_64K_IPS_FIELD;

		return ips == GAMW_ECO_ENABLE_64K_IPS_FIELD;
	} else if (INTEL_GEN(dev_priv) >= 11) {
		/* 64K paging only controlled by IPS bit in PTE now. */
		return true;
	} else
		return false;
}