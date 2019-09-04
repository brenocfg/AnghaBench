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
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIU_MISC_CTRL1 ; 
 int /*<<< orphan*/  VPP_DOLBY_CTRL ; 
 int /*<<< orphan*/  VPP_DUMMY_DATA1 ; 
 int /*<<< orphan*/  VPP_HOLD_LINES ; 
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_OFIFO_SIZE ; 
 int VPP_OSD1_POSTBLEND ; 
 int VPP_OSD2_POSTBLEND ; 
 int /*<<< orphan*/  VPP_OSD_HSC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_SC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_VSC_CTRL0 ; 
 int VPP_POSTBLEND_ENABLE ; 
 int VPP_PREBLEND_ENABLE ; 
 int VPP_VD1_POSTBLEND ; 
 int VPP_VD2_POSTBLEND ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_vpp_write_scaling_filter_coefs (struct meson_drm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,char*) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  vpp_filter_coefs_4point_bspline ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_vpp_init(struct meson_drm *priv)
{
	/* set dummy data default YUV black */
	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		writel_relaxed(0x108080, priv->io_base + _REG(VPP_DUMMY_DATA1));
	else if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu")) {
		writel_bits_relaxed(0xff << 16, 0xff << 16,
				    priv->io_base + _REG(VIU_MISC_CTRL1));
		writel_relaxed(0x20000, priv->io_base + _REG(VPP_DOLBY_CTRL));
		writel_relaxed(0x1020080,
				priv->io_base + _REG(VPP_DUMMY_DATA1));
	}

	/* Initialize vpu fifo control registers */
	writel_relaxed(readl_relaxed(priv->io_base + _REG(VPP_OFIFO_SIZE)) |
			0x77f, priv->io_base + _REG(VPP_OFIFO_SIZE));
	writel_relaxed(0x08080808, priv->io_base + _REG(VPP_HOLD_LINES));

	/* Turn off preblend */
	writel_bits_relaxed(VPP_PREBLEND_ENABLE, 0,
			    priv->io_base + _REG(VPP_MISC));

	/* Turn off POSTBLEND */
	writel_bits_relaxed(VPP_POSTBLEND_ENABLE, 0,
			    priv->io_base + _REG(VPP_MISC));

	/* Force all planes off */
	writel_bits_relaxed(VPP_OSD1_POSTBLEND | VPP_OSD2_POSTBLEND |
			    VPP_VD1_POSTBLEND | VPP_VD2_POSTBLEND, 0,
			    priv->io_base + _REG(VPP_MISC));

	/* Disable Scalers */
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_SC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_VSC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_HSC_CTRL0));

	/* Write in the proper filter coefficients. */
	meson_vpp_write_scaling_filter_coefs(priv,
				vpp_filter_coefs_4point_bspline, false);
	meson_vpp_write_scaling_filter_coefs(priv,
				vpp_filter_coefs_4point_bspline, true);
}