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
struct mipi_dsi_device {int dummy; } ;
struct dw_mipi_dsi_rockchip {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  component_del (struct device*,int /*<<< orphan*/ *) ; 
 struct device* dw_mipi_dsi_rockchip_find_second (struct dw_mipi_dsi_rockchip*) ; 
 int /*<<< orphan*/  dw_mipi_dsi_rockchip_ops ; 

__attribute__((used)) static int dw_mipi_dsi_rockchip_host_detach(void *priv_data,
					    struct mipi_dsi_device *device)
{
	struct dw_mipi_dsi_rockchip *dsi = priv_data;
	struct device *second;

	second = dw_mipi_dsi_rockchip_find_second(dsi);
	if (second && !IS_ERR(second))
		component_del(second, &dw_mipi_dsi_rockchip_ops);

	component_del(dsi->dev, &dw_mipi_dsi_rockchip_ops);

	return 0;
}