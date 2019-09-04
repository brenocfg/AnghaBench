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
typedef  int /*<<< orphan*/  u8 ;
struct imx_ldb_channel {int mode_valid; int /*<<< orphan*/  bus_flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  panel; int /*<<< orphan*/  edid_len; int /*<<< orphan*/  edid; int /*<<< orphan*/  ddc; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OF_USE_NATIVE_MODE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_find_i2c_adapter_by_node (struct device_node*) ; 
 int of_get_drm_display_mode (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_ldb_panel_ddc(struct device *dev,
		struct imx_ldb_channel *channel, struct device_node *child)
{
	struct device_node *ddc_node;
	const u8 *edidp;
	int ret;

	ddc_node = of_parse_phandle(child, "ddc-i2c-bus", 0);
	if (ddc_node) {
		channel->ddc = of_find_i2c_adapter_by_node(ddc_node);
		of_node_put(ddc_node);
		if (!channel->ddc) {
			dev_warn(dev, "failed to get ddc i2c adapter\n");
			return -EPROBE_DEFER;
		}
	}

	if (!channel->ddc) {
		/* if no DDC available, fallback to hardcoded EDID */
		dev_dbg(dev, "no ddc available\n");

		edidp = of_get_property(child, "edid",
					&channel->edid_len);
		if (edidp) {
			channel->edid = kmemdup(edidp,
						channel->edid_len,
						GFP_KERNEL);
		} else if (!channel->panel) {
			/* fallback to display-timings node */
			ret = of_get_drm_display_mode(child,
						      &channel->mode,
						      &channel->bus_flags,
						      OF_USE_NATIVE_MODE);
			if (!ret)
				channel->mode_valid = 1;
		}
	}
	return 0;
}