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
 int /*<<< orphan*/  VPU_COMPATIBLE_GXBB ; 
 unsigned int XTAL_FREQ ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int meson_hdmi_pll_get_m(struct meson_drm *priv,
					 unsigned int pll_freq)
{
	/* The GXBB PLL has a /2 pre-multiplier */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXBB))
		pll_freq /= 2;

	return pll_freq / XTAL_FREQ;
}