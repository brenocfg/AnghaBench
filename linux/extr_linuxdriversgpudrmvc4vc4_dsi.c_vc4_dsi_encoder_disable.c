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
struct vc4_dsi_encoder {struct vc4_dsi* dsi; } ;
struct vc4_dsi {int /*<<< orphan*/  pixel_clock; int /*<<< orphan*/  escape_clock; int /*<<< orphan*/  pll_phy_clock; int /*<<< orphan*/  bridge; TYPE_1__* pdev; } ;
struct drm_encoder {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_bridge_post_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 struct vc4_dsi_encoder* to_vc4_dsi_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  vc4_dsi_ulps (struct vc4_dsi*,int) ; 

__attribute__((used)) static void vc4_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct vc4_dsi_encoder *vc4_encoder = to_vc4_dsi_encoder(encoder);
	struct vc4_dsi *dsi = vc4_encoder->dsi;
	struct device *dev = &dsi->pdev->dev;

	drm_bridge_disable(dsi->bridge);
	vc4_dsi_ulps(dsi, true);
	drm_bridge_post_disable(dsi->bridge);

	clk_disable_unprepare(dsi->pll_phy_clock);
	clk_disable_unprepare(dsi->escape_clock);
	clk_disable_unprepare(dsi->pixel_clock);

	pm_runtime_put(dev);
}