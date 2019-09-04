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
struct drm_rect {int x1; int x2; int y1; int y2; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  VPP_OSD_HSC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_SCI_WH_M1 ; 
 int /*<<< orphan*/  VPP_OSD_SCO_H_START_END ; 
 int /*<<< orphan*/  VPP_OSD_SCO_V_START_END ; 
 int /*<<< orphan*/  VPP_OSD_SC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_VSC_CTRL0 ; 
 int /*<<< orphan*/  VPP_OSD_VSC_INI_PHASE ; 
 int /*<<< orphan*/  VPP_OSD_VSC_PHASE_STEP ; 
 scalar_t__ _REG (int /*<<< orphan*/ ) ; 
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

void meson_vpp_setup_interlace_vscaler_osd1(struct meson_drm *priv,
					    struct drm_rect *input)
{
	writel_relaxed(BIT(3) /* Enable scaler */ |
		       BIT(2), /* Select OSD1 */
			priv->io_base + _REG(VPP_OSD_SC_CTRL0));

	writel_relaxed(((drm_rect_width(input) - 1) << 16) |
		       (drm_rect_height(input) - 1),
			priv->io_base + _REG(VPP_OSD_SCI_WH_M1));
	/* 2:1 scaling */
	writel_relaxed(((input->x1) << 16) | (input->x2),
			priv->io_base + _REG(VPP_OSD_SCO_H_START_END));
	writel_relaxed(((input->y1 >> 1) << 16) | (input->y2 >> 1),
			priv->io_base + _REG(VPP_OSD_SCO_V_START_END));

	/* 2:1 scaling values */
	writel_relaxed(BIT(16), priv->io_base + _REG(VPP_OSD_VSC_INI_PHASE));
	writel_relaxed(BIT(25), priv->io_base + _REG(VPP_OSD_VSC_PHASE_STEP));

	writel_relaxed(0, priv->io_base + _REG(VPP_OSD_HSC_CTRL0));

	writel_relaxed((4 << 0) /* osd_vsc_bank_length */ |
		       (4 << 3) /* osd_vsc_top_ini_rcv_num0 */ |
		       (1 << 8) /* osd_vsc_top_rpt_p0_num0 */ |
		       (6 << 11) /* osd_vsc_bot_ini_rcv_num0 */ |
		       (2 << 16) /* osd_vsc_bot_rpt_p0_num0 */ |
		       BIT(23)	/* osd_prog_interlace */ |
		       BIT(24), /* Enable vertical scaler */
			priv->io_base + _REG(VPP_OSD_VSC_CTRL0));
}