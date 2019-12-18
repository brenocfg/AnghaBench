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
typedef  int uint32_t ;
struct TYPE_2__ {int osd1_enabled; int osd1_commit; int osd1_interlace; } ;
struct meson_drm {TYPE_1__ viu; scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFBC_ENABLE ; 
 int DOLBY_BYPASS_EN (int) ; 
 int /*<<< orphan*/  DOLBY_PATH_CTRL ; 
 int /*<<< orphan*/  OSD1_BLEND_SRC_CTRL ; 
 int /*<<< orphan*/  OSD2_BLEND_SRC_CTRL ; 
 int OSD_BLEND_PATH_SEL_ENABLE ; 
 int OSD_REPLACE_SHIFT ; 
 int /*<<< orphan*/  RGB709_to_YUV709l_coeff ; 
 int /*<<< orphan*/  VD1_BLEND_SRC_CTRL ; 
 int /*<<< orphan*/  VD1_IF0_LUMA_FIFO_SIZE ; 
 int /*<<< orphan*/  VD2_BLEND_SRC_CTRL ; 
 int /*<<< orphan*/  VD2_IF0_LUMA_FIFO_SIZE ; 
 int VIU_CTRL0_VD1_AFBC_MASK ; 
 int /*<<< orphan*/  VIU_MISC_CTRL0 ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT2 ; 
 int /*<<< orphan*/  VIU_OSD1_FIFO_CTRL_STAT ; 
 int VIU_OSD1_OSD_BLK_ENABLE ; 
 int VIU_OSD1_OSD_ENABLE ; 
 int /*<<< orphan*/  VIU_OSD2_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_OSD2_CTRL_STAT2 ; 
 int /*<<< orphan*/  VIU_OSD2_FIFO_CTRL_STAT ; 
 int VIU_OSD_BLEND1_DIN3_BYPASS_TO_DOUT1 ; 
 int VIU_OSD_BLEND1_DOUT_BYPASS_TO_BLEND2 ; 
 int VIU_OSD_BLEND_BLEN2_PREMULT_EN (int) ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_CTRL ; 
 int VIU_OSD_BLEND_DIN0_BYPASS_TO_DOUT0 ; 
 int VIU_OSD_BLEND_DIN_EN (int) ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_DUMMY_ALPHA ; 
 int /*<<< orphan*/  VIU_OSD_BLEND_DUMMY_DATA0 ; 
 int VIU_OSD_BLEND_HOLD_LINES (int) ; 
 int VIU_OSD_BLEND_REORDER (int,int) ; 
 int VIU_OSD_DDR_PRIORITY_URGENT ; 
 int VIU_OSD_FIFO_DEPTH_VAL (int) ; 
 int VIU_OSD_FIFO_LIMITS (int) ; 
 int VIU_OSD_HOLD_FIFO_LINES (int) ; 
 int VIU_OSD_WORDS_PER_BURST (int) ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_G12A ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXL ; 
 int /*<<< orphan*/  VPU_COMPATIBLE_GXM ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_viu_load_matrix (struct meson_drm*) ; 
 int meson_viu_osd_burst_length_reg (int) ; 
 int /*<<< orphan*/  meson_viu_set_g12a_osd1_matrix (struct meson_drm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_viu_init(struct meson_drm *priv)
{
	uint32_t reg;

	/* Disable OSDs */
	writel_bits_relaxed(VIU_OSD1_OSD_BLK_ENABLE | VIU_OSD1_OSD_ENABLE, 0,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT));
	writel_bits_relaxed(VIU_OSD1_OSD_BLK_ENABLE | VIU_OSD1_OSD_ENABLE, 0,
			    priv->io_base + _REG(VIU_OSD2_CTRL_STAT));

	/* On GXL/GXM, Use the 10bit HDR conversion matrix */
	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXM) ||
	    meson_vpu_is_compatible(priv, VPU_COMPATIBLE_GXL))
		meson_viu_load_matrix(priv);
	else if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		meson_viu_set_g12a_osd1_matrix(priv, RGB709_to_YUV709l_coeff,
					       true);

	/* Initialize OSD1 fifo control register */
	reg = VIU_OSD_DDR_PRIORITY_URGENT |
		VIU_OSD_HOLD_FIFO_LINES(4) |
		VIU_OSD_FIFO_DEPTH_VAL(32) | /* fifo_depth_val: 32*8=256 */
		VIU_OSD_WORDS_PER_BURST(4) | /* 4 words in 1 burst */
		VIU_OSD_FIFO_LIMITS(2);      /* fifo_lim: 2*16=32 */

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A))
		reg |= meson_viu_osd_burst_length_reg(32);
	else
		reg |= meson_viu_osd_burst_length_reg(64);

	writel_relaxed(reg, priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	writel_relaxed(reg, priv->io_base + _REG(VIU_OSD2_FIFO_CTRL_STAT));

	/* Set OSD alpha replace value */
	writel_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
	writel_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD2_CTRL_STAT2));

	/* Disable VD1 AFBC */
	/* di_mif0_en=0 mif0_to_vpp_en=0 di_mad_en=0 and afbc vd1 set=0*/
	writel_bits_relaxed(VIU_CTRL0_VD1_AFBC_MASK, 0,
			    priv->io_base + _REG(VIU_MISC_CTRL0));
	writel_relaxed(0, priv->io_base + _REG(AFBC_ENABLE));

	writel_relaxed(0x00FF00C0,
			priv->io_base + _REG(VD1_IF0_LUMA_FIFO_SIZE));
	writel_relaxed(0x00FF00C0,
			priv->io_base + _REG(VD2_IF0_LUMA_FIFO_SIZE));

	if (meson_vpu_is_compatible(priv, VPU_COMPATIBLE_G12A)) {
		writel_relaxed(VIU_OSD_BLEND_REORDER(0, 1) |
			       VIU_OSD_BLEND_REORDER(1, 0) |
			       VIU_OSD_BLEND_REORDER(2, 0) |
			       VIU_OSD_BLEND_REORDER(3, 0) |
			       VIU_OSD_BLEND_DIN_EN(1) |
			       VIU_OSD_BLEND1_DIN3_BYPASS_TO_DOUT1 |
			       VIU_OSD_BLEND1_DOUT_BYPASS_TO_BLEND2 |
			       VIU_OSD_BLEND_DIN0_BYPASS_TO_DOUT0 |
			       VIU_OSD_BLEND_BLEN2_PREMULT_EN(1) |
			       VIU_OSD_BLEND_HOLD_LINES(4),
			       priv->io_base + _REG(VIU_OSD_BLEND_CTRL));

		writel_relaxed(OSD_BLEND_PATH_SEL_ENABLE,
			       priv->io_base + _REG(OSD1_BLEND_SRC_CTRL));
		writel_relaxed(OSD_BLEND_PATH_SEL_ENABLE,
			       priv->io_base + _REG(OSD2_BLEND_SRC_CTRL));
		writel_relaxed(0, priv->io_base + _REG(VD1_BLEND_SRC_CTRL));
		writel_relaxed(0, priv->io_base + _REG(VD2_BLEND_SRC_CTRL));
		writel_relaxed(0,
				priv->io_base + _REG(VIU_OSD_BLEND_DUMMY_DATA0));
		writel_relaxed(0,
				priv->io_base + _REG(VIU_OSD_BLEND_DUMMY_ALPHA));

		writel_bits_relaxed(DOLBY_BYPASS_EN(0xc), DOLBY_BYPASS_EN(0xc),
				    priv->io_base + _REG(DOLBY_PATH_CTRL));
	}

	priv->viu.osd1_enabled = false;
	priv->viu.osd1_commit = false;
	priv->viu.osd1_interlace = false;
}