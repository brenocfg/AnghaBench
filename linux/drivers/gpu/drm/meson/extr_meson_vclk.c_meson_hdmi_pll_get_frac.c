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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct meson_drm {int dummy; } ;

/* Variables and functions */
 unsigned int HDMI_FRAC_MAX_G12A ; 
 unsigned int HDMI_FRAC_MAX_GXBB ; 
 unsigned int HDMI_FRAC_MAX_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXBB ; 
 unsigned int XTAL_FREQ ; 
 unsigned int div_u64 (int,unsigned int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 unsigned int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int meson_hdmi_pll_get_frac(struct meson_drm *priv,
					    unsigned int m,
					    unsigned int pll_freq)
{
	unsigned int parent_freq = XTAL_FREQ;
	unsigned int frac_max = HDMI_FRAC_MAX_GXL;
	unsigned int frac_m;
	unsigned int frac;

	/* The GXBB PLL has a /2 pre-multiplier and a larger FRAC width */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB)) {
		frac_max = HDMI_FRAC_MAX_GXBB;
		parent_freq *= 2;
	}

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		frac_max = HDMI_FRAC_MAX_G12A;

	/* We can have a perfect match !*/
	if (pll_freq / m == parent_freq &&
	    pll_freq % m == 0)
		return 0;

	frac = div_u64((u64)pll_freq * (u64)frac_max, parent_freq);
	frac_m = m * frac_max;
	if (frac_m > frac)
		return frac_max;
	frac -= frac_m;

	return min((u16)frac, (u16)(frac_max - 1));
}