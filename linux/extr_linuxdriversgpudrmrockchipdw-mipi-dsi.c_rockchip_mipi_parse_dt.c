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
struct dw_mipi_dsi {int /*<<< orphan*/  grf_regmap; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_1__*,char*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int rockchip_mipi_parse_dt(struct dw_mipi_dsi *dsi)
{
	struct device_node *np = dsi->dev->of_node;

	dsi->grf_regmap = syscon_regmap_lookup_by_phandle(np, "rockchip,grf");
	if (IS_ERR(dsi->grf_regmap)) {
		DRM_DEV_ERROR(dsi->dev, "Unable to get rockchip,grf\n");
		return PTR_ERR(dsi->grf_regmap);
	}

	return 0;
}