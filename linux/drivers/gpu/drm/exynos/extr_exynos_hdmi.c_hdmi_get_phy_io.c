#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hdmi_context {int /*<<< orphan*/  hdmiphy_port; TYPE_2__* dev; int /*<<< orphan*/  regs_hdmiphy; TYPE_1__* drv_data; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {scalar_t__ is_apb_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  of_find_i2c_device_by_node (struct device_node*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_get_phy_io(struct hdmi_context *hdata)
{
	const char *compatible_str = "samsung,exynos4212-hdmiphy";
	struct device_node *np;
	int ret = 0;

	np = of_find_compatible_node(NULL, NULL, compatible_str);
	if (!np) {
		np = of_parse_phandle(hdata->dev->of_node, "phy", 0);
		if (!np) {
			DRM_DEV_ERROR(hdata->dev,
				      "Failed to find hdmiphy node in device tree\n");
			return -ENODEV;
		}
	}

	if (hdata->drv_data->is_apb_phy) {
		hdata->regs_hdmiphy = of_iomap(np, 0);
		if (!hdata->regs_hdmiphy) {
			DRM_DEV_ERROR(hdata->dev,
				      "failed to ioremap hdmi phy\n");
			ret = -ENOMEM;
			goto out;
		}
	} else {
		hdata->hdmiphy_port = of_find_i2c_device_by_node(np);
		if (!hdata->hdmiphy_port) {
			DRM_INFO("Failed to get hdmi phy i2c client\n");
			ret = -EPROBE_DEFER;
			goto out;
		}
	}

out:
	of_node_put(np);
	return ret;
}