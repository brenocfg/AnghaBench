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
 int /*<<< orphan*/  DOLBY_PATH_CTRL ; 
 int /*<<< orphan*/  VIU_MISC_CTRL1 ; 
 int /*<<< orphan*/  VPP_BLEND_VD2_H_START_END ; 
 int /*<<< orphan*/  VPP_DOLBY_CTRL ; 
 int /*<<< orphan*/  VPP_DUMMY_DATA1 ; 
 int /*<<< orphan*/  VPP_HOLD_LINES ; 
 int VPP_HSC_BANK_LENGTH (int) ; 
 int VPP_MINUS_BLACK_LVL_VADJ1_ENABLE ; 
 int /*<<< orphan*/  VPP_MISC ; 
 int /*<<< orphan*/  VPP_OFIFO_SIZE ; 
 int VPP_OFIFO_SIZE_DEFAULT ; 
 int VPP_OFIFO_SIZE_MASK ; 
 int VPP_OSD1_POSTBLEND ; 
 int VPP_OSD2_POSTBLEND ; 
 int /*<<< orphan*/  VPP_OSD_HSC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_SC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_VSC_CTRL0 ; 
 int VPP_POSTBLEND_ENABLE ; 
 int VPP_POSTBLEND_HOLD_LINES (int) ; 
 int VPP_PPS_DUMMY_DATA_MODE ; 
 int VPP_PREBLEND_ENABLE ; 
 int VPP_PREBLEND_HOLD_LINES (int) ; 
 int /*<<< orphan*/  VPP_PREBLEND_VD1_H_START_END ; 
 int /*<<< orphan*/  VPP_SC_MISC ; 
 int VPP_SC_VD_EN_ENABLE ; 
 int /*<<< orphan*/  VPP_VADJ_CTRL ; 
 int VPP_VD1_POSTBLEND ; 
 int VPP_VD1_PREBLEND ; 
 int VPP_VD2_POSTBLEND ; 
 int VPP_VD2_PREBLEND ; 
 int VPP_VSC_BANK_LENGTH (int) ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXM ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_vpp_write_scaling_filter_coefs (struct meson_drm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  meson_vpp_write_vd_scaling_filter_coefs (struct meson_drm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpp_filter_coefs_4point_bspline ; 
 int /*<<< orphan*/  vpp_filter_coefs_bicubic ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_vpp_init(struct meson_drm *priv)
{
	/* set dummy data default YUV black */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		writel_relaxed(0x108080, priv->io_base + _REG(VPP_DUMMY_DATA1));
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM)) {
		writel_bits_relaxed(0xff << 16, 0xff << 16,
				    priv->io_base + _REG(VIU_MISC_CTRL1));
		writel_relaxed(VPP_PPS_DUMMY_DATA_MODE,
			       priv->io_base + _REG(VPP_DOLBY_CTRL));
		writel_relaxed(0x1020080,
				priv->io_base + _REG(VPP_DUMMY_DATA1));
	} else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		writel_relaxed(0xf, priv->io_base + _REG(DOLBY_PATH_CTRL));

	/* Initialize vpu fifo control registers */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		writel_relaxed(VPP_OFIFO_SIZE_DEFAULT,
			       priv->io_base + _REG(VPP_OFIFO_SIZE));
	else
		writel_bits_relaxed(VPP_OFIFO_SIZE_MASK, 0x77f,
				    priv->io_base + _REG(VPP_OFIFO_SIZE));
	writel_relaxed(VPP_POSTBLEND_HOLD_LINES(4) | VPP_PREBLEND_HOLD_LINES(4),
		       priv->io_base + _REG(VPP_HOLD_LINES));

	if (!meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		/* Turn off preblend */
		writel_bits_relaxed(VPP_PREBLEND_ENABLE, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Turn off POSTBLEND */
		writel_bits_relaxed(VPP_POSTBLEND_ENABLE, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Force all planes off */
		writel_bits_relaxed(VPP_OSD1_POSTBLEND | VPP_OSD2_POSTBLEND |
				    VPP_VD1_POSTBLEND | VPP_VD2_POSTBLEND |
				    VPP_VD1_PREBLEND | VPP_VD2_PREBLEND, 0,
				    priv->io_base + _REG(VPP_MISC));

		/* Setup default VD settings */
		writel_relaxed(4096,
				priv->io_base + _REG(VPP_PREBLEND_VD1_H_START_END));
		writel_relaxed(4096,
				priv->io_base + _REG(VPP_BLEND_VD2_H_START_END));
	}

	/* Disable Scalers */
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_SC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_VSC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_HSC_CTRL0));

	/* Set horizontal/vertical bank length and enable video scale out */
	writel_relaxed(VPP_VSC_BANK_LENGTH(4) | VPP_HSC_BANK_LENGTH(4) |
		       VPP_SC_VD_EN_ENABLE,
		       priv->io_base + _REG(VPP_SC_MISC));

	/* Enable minus black level for vadj1 */
	writel_relaxed(VPP_MINUS_BLACK_LVL_VADJ1_ENABLE,
		       priv->io_base + _REG(VPP_VADJ_CTRL));

	/* Write in the proper filter coefficients. */
	meson_vpp_write_scaling_filter_coefs(priv,
				vpp_filter_coefs_4point_bspline, false);
	meson_vpp_write_scaling_filter_coefs(priv,
				vpp_filter_coefs_4point_bspline, true);

	/* Write the VD proper filter coefficients. */
	meson_vpp_write_vd_scaling_filter_coefs(priv, vpp_filter_coefs_bicubic,
						false);
	meson_vpp_write_vd_scaling_filter_coefs(priv, vpp_filter_coefs_bicubic,
						true);
}