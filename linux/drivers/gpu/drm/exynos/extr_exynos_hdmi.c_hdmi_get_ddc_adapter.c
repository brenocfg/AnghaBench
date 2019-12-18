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
struct i2c_adapter {int dummy; } ;
struct hdmi_context {struct i2c_adapter* ddc_adpt; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 struct i2c_adapter* of_find_i2c_adapter_by_node (struct device_node*) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdmi_get_ddc_adapter(struct hdmi_context *hdata)
{
	const char *compatible_str = "samsung,exynos4210-hdmiddc";
	struct device_node *np;
	struct i2c_adapter *adpt;

	np = of_find_compatible_node(NULL, NULL, compatible_str);
	if (np)
		np = of_get_next_parent(np);
	else
		np = of_parse_phandle(hdata->dev->of_node, "ddc", 0);

	if (!np) {
		DRM_DEV_ERROR(hdata->dev,
			      "Failed to find ddc node in device tree\n");
		return -ENODEV;
	}

	adpt = of_find_i2c_adapter_by_node(np);
	of_node_put(np);

	if (!adpt) {
		DRM_INFO("Failed to get ddc i2c adapter by node\n");
		return -EPROBE_DEFER;
	}

	hdata->ddc_adpt = adpt;

	return 0;
}