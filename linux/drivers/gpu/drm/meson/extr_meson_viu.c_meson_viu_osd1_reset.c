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
typedef  int /*<<< orphan*/  uint32_t ;
struct meson_drm {scalar_t__ io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIU_OSD1_CTRL_STAT2 ; 
 int /*<<< orphan*/  VIU_OSD1_FIFO_CTRL_STAT ; 
 int /*<<< orphan*/  VIU_SW_RESET ; 
 int /*<<< orphan*/  VIU_SW_RESET_OSD1 ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_viu_load_matrix (struct meson_drm*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_bits_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void meson_viu_osd1_reset(struct meson_drm *priv)
{
	uint32_t osd1_fifo_ctrl_stat, osd1_ctrl_stat2;

	/* Save these 2 registers state */
	osd1_fifo_ctrl_stat = readl_relaxed(
				priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	osd1_ctrl_stat2 = readl_relaxed(
				priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));

	/* Reset OSD1 */
	writel_bits_relaxed(VIU_SW_RESET_OSD1, VIU_SW_RESET_OSD1,
			    priv->io_base + _REG(VIU_SW_RESET));
	writel_bits_relaxed(VIU_SW_RESET_OSD1, 0,
			    priv->io_base + _REG(VIU_SW_RESET));

	/* Rewrite these registers state lost in the reset */
	writel_relaxed(osd1_fifo_ctrl_stat,
		       priv->io_base + _REG(VIU_OSD1_FIFO_CTRL_STAT));
	writel_relaxed(osd1_ctrl_stat2,
		       priv->io_base + _REG(VIU_OSD1_CTRL_STAT2));

	/* Reload the conversion matrix */
	meson_viu_load_matrix(priv);
}