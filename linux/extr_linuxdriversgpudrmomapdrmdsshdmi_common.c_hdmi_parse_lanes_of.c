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
typedef  int u32 ;
struct property {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_phy_data {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hdmi_phy_parse_lanes (struct hdmi_phy_data*,int const*) ; 
 struct property* of_find_property (struct device_node*,char*,int*) ; 
 int of_property_read_u32_array (struct device_node*,char*,int*,int) ; 

int hdmi_parse_lanes_of(struct platform_device *pdev, struct device_node *ep,
	struct hdmi_phy_data *phy)
{
	struct property *prop;
	int r, len;

	prop = of_find_property(ep, "lanes", &len);
	if (prop) {
		u32 lanes[8];

		if (len / sizeof(u32) != ARRAY_SIZE(lanes)) {
			dev_err(&pdev->dev, "bad number of lanes\n");
			return -EINVAL;
		}

		r = of_property_read_u32_array(ep, "lanes", lanes,
			ARRAY_SIZE(lanes));
		if (r) {
			dev_err(&pdev->dev, "failed to read lane data\n");
			return r;
		}

		r = hdmi_phy_parse_lanes(phy, lanes);
		if (r) {
			dev_err(&pdev->dev, "failed to parse lane data\n");
			return r;
		}
	} else {
		static const u32 default_lanes[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

		r = hdmi_phy_parse_lanes(phy, default_lanes);
		if (WARN_ON(r)) {
			dev_err(&pdev->dev, "failed to parse lane data\n");
			return r;
		}
	}

	return 0;
}