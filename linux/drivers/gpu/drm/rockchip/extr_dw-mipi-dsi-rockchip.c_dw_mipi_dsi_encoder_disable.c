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
struct dw_mipi_dsi_rockchip {int /*<<< orphan*/  dev; TYPE_1__* slave; } ;
struct drm_encoder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 struct dw_mipi_dsi_rockchip* to_dsi (struct drm_encoder*) ; 

__attribute__((used)) static void dw_mipi_dsi_encoder_disable(struct drm_encoder *encoder)
{
	struct dw_mipi_dsi_rockchip *dsi = to_dsi(encoder);

	if (dsi->slave)
		pm_runtime_put(dsi->slave->dev);
	pm_runtime_put(dsi->dev);
}