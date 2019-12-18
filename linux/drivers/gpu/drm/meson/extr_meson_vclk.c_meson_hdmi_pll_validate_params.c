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
struct meson_drm {int dummy; } ;

/* Variables and functions */
 unsigned int HDMI_FRAC_MAX_GXBB ; 
 unsigned int HDMI_FRAC_MAX_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXBB ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXM ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool meson_hdmi_pll_validate_params(struct meson_drm *priv,
					   unsigned int m,
					   unsigned int frac)
{
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) {
		/* Empiric supported min/max dividers */
		if (m < 53 || m > 123)
			return false;
		if (frac >= HDMI_FRAC_MAX_GXBB)
			return false;
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL) ||
		   meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		/* Empiric supported min/max dividers */
		if (m < 106 || m > 247)
			return false;
		if (frac >= HDMI_FRAC_MAX_GXL)
			return false;
	}

	return true;
}