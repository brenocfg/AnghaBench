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
struct drm_encoder {int /*<<< orphan*/  crtc; } ;
struct exynos_dsi {int state; struct drm_encoder encoder; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DSIM_STATE_VIDOUT_AVAILABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  exynos_drm_crtc_te_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t exynos_dsi_te_irq_handler(int irq, void *dev_id)
{
	struct exynos_dsi *dsi = (struct exynos_dsi *)dev_id;
	struct drm_encoder *encoder = &dsi->encoder;

	if (dsi->state & DSIM_STATE_VIDOUT_AVAILABLE)
		exynos_drm_crtc_te_handler(encoder->crtc);

	return IRQ_HANDLED;
}