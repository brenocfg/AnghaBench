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
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_display_mode {int hsync_end; int hsync_start; int vsync_end; int vsync_start; int htotal; int hdisplay; int vtotal; int vdisplay; } ;
struct drm_device {struct hibmc_drm_private* dev_private; } ;
struct drm_crtc {struct drm_device* dev; TYPE_1__* state; } ;
struct TYPE_2__ {struct drm_display_mode mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIBMC_CRT_DISP_CTL_HSYNC_PHASE ; 
 unsigned int HIBMC_CRT_DISP_CTL_PLANE (int) ; 
 unsigned int HIBMC_CRT_DISP_CTL_TIMING (int) ; 
 int /*<<< orphan*/  HIBMC_CRT_DISP_CTL_VSYNC_PHASE ; 
 scalar_t__ HIBMC_CRT_HORZ_SYNC ; 
 int /*<<< orphan*/  HIBMC_CRT_HORZ_SYNC_START ; 
 int /*<<< orphan*/  HIBMC_CRT_HORZ_SYNC_WIDTH ; 
 scalar_t__ HIBMC_CRT_HORZ_TOTAL ; 
 int /*<<< orphan*/  HIBMC_CRT_HORZ_TOTAL_DISP_END ; 
 int /*<<< orphan*/  HIBMC_CRT_HORZ_TOTAL_TOTAL ; 
 scalar_t__ HIBMC_CRT_PLL_CTRL ; 
 scalar_t__ HIBMC_CRT_VERT_SYNC ; 
 int /*<<< orphan*/  HIBMC_CRT_VERT_SYNC_HEIGHT ; 
 int /*<<< orphan*/  HIBMC_CRT_VERT_SYNC_START ; 
 scalar_t__ HIBMC_CRT_VERT_TOTAL ; 
 int /*<<< orphan*/  HIBMC_CRT_VERT_TOTAL_DISP_END ; 
 int /*<<< orphan*/  HIBMC_CRT_VERT_TOTAL_TOTAL ; 
 unsigned int HIBMC_FIELD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  display_ctrl_adjust (struct drm_device*,struct drm_display_mode*,unsigned int) ; 
 unsigned int format_pll_reg () ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void hibmc_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	unsigned int val;
	struct drm_display_mode *mode = &crtc->state->mode;
	struct drm_device *dev = crtc->dev;
	struct hibmc_drm_private *priv = dev->dev_private;
	int width = mode->hsync_end - mode->hsync_start;
	int height = mode->vsync_end - mode->vsync_start;

	writel(format_pll_reg(), priv->mmio + HIBMC_CRT_PLL_CTRL);
	writel(HIBMC_FIELD(HIBMC_CRT_HORZ_TOTAL_TOTAL, mode->htotal - 1) |
	       HIBMC_FIELD(HIBMC_CRT_HORZ_TOTAL_DISP_END, mode->hdisplay - 1),
	       priv->mmio + HIBMC_CRT_HORZ_TOTAL);

	writel(HIBMC_FIELD(HIBMC_CRT_HORZ_SYNC_WIDTH, width) |
	       HIBMC_FIELD(HIBMC_CRT_HORZ_SYNC_START, mode->hsync_start - 1),
	       priv->mmio + HIBMC_CRT_HORZ_SYNC);

	writel(HIBMC_FIELD(HIBMC_CRT_VERT_TOTAL_TOTAL, mode->vtotal - 1) |
	       HIBMC_FIELD(HIBMC_CRT_VERT_TOTAL_DISP_END, mode->vdisplay - 1),
	       priv->mmio + HIBMC_CRT_VERT_TOTAL);

	writel(HIBMC_FIELD(HIBMC_CRT_VERT_SYNC_HEIGHT, height) |
	       HIBMC_FIELD(HIBMC_CRT_VERT_SYNC_START, mode->vsync_start - 1),
	       priv->mmio + HIBMC_CRT_VERT_SYNC);

	val = HIBMC_FIELD(HIBMC_CRT_DISP_CTL_VSYNC_PHASE, 0);
	val |= HIBMC_FIELD(HIBMC_CRT_DISP_CTL_HSYNC_PHASE, 0);
	val |= HIBMC_CRT_DISP_CTL_TIMING(1);
	val |= HIBMC_CRT_DISP_CTL_PLANE(1);

	display_ctrl_adjust(dev, mode, val);
}