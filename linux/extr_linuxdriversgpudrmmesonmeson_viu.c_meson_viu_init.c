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
 int BIT (int) ; 
 int OSD_REPLACE_SHIFT ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT2 ; 
 int /*<<< orphan*/  VIU_OSD1_FIFO_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_OSD2_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_OSD2_CTRL_STAT2 ; 
 int /*<<< orphan*/  VIU_OSD2_FIFO_CTRL_STAT ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_viu_load_matrix (struct meson_drm*) ; 
 scalar_t__ meson_vpu_is_compatible (struct meson_drm*,char*) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int,int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_viu_init(struct meson_drm *priv)
{
	uint32_t reg;

	/* Disable OSDs */
	writel_bits_relaxed(BIT(0) | BIT(21), 0,
			priv->io_base + _REG(VIU_OSD1_CTRL_STAT));
	writel_bits_relaxed(BIT(0) | BIT(21), 0,
			priv->io_base + _REG(VIU_OSD2_CTRL_STAT));

	/* On GXL/GXM, Use the 10bit HDR conversion matrix */
	if (meson_vpu_is_compatible(priv, "amlogic,meson-gxm-vpu") ||
	    meson_vpu_is_compatible(priv, "amlogic,meson-gxl-vpu"))
		meson_viu_load_matrix(priv);

	/* Initialize OSD1 fifo control register */
	reg = BIT(0) |	/* Urgent DDR request priority */
	      (4 << 5) | /* hold_fifo_lines */
	      (3 << 10) | /* burst length 64 */
	      (32 << 12) | /* fifo_depth_val: 32*8=256 */
	      (2 << 22) | /* 4 words in 1 burst */
	      (2 << 24);
	writel_relaxed(reg, priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	writel_relaxed(reg, priv->io_base + _REG(VIU_OSD2_FIFO_CTRL_STAT));

	/* Set OSD alpha replace value */
	writel_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));
	writel_bits_relaxed(0xff << OSD_REPLACE_SHIFT,
			    0xff << OSD_REPLACE_SHIFT,
			    priv->io_base + _REG(VIU_OSD2_CTRL_STAT2));

	priv->viu.osd1_enabled = false;
	priv->viu.osd1_commit = false;
	priv->viu.osd1_interlace = false;
}