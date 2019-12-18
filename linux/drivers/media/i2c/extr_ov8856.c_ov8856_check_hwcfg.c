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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ num_data_lanes; } ;
struct TYPE_4__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {unsigned int nr_of_link_frequencies; scalar_t__* link_frequencies; TYPE_2__ bus; int /*<<< orphan*/  bus_type; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ OV8856_DATA_LANES ; 
 scalar_t__ OV8856_MCLK ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int fwnode_property_read_u32 (struct fwnode_handle*,char*,scalar_t__*) ; 
 scalar_t__* link_freq_menu_items ; 
 int v4l2_fwnode_endpoint_alloc_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_free (struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int ov8856_check_hwcfg(struct device *dev)
{
	struct fwnode_handle *ep;
	struct fwnode_handle *fwnode = dev_fwnode(dev);
	struct v4l2_fwnode_endpoint bus_cfg = {
		.bus_type = V4L2_MBUS_CSI2_DPHY
	};
	u32 mclk;
	int ret;
	unsigned int i, j;

	if (!fwnode)
		return -ENXIO;

	ret = fwnode_property_read_u32(fwnode, "clock-frequency", &mclk);
	if (ret)
		return ret;

	if (mclk != OV8856_MCLK) {
		dev_err(dev, "external clock %d is not supported", mclk);
		return -EINVAL;
	}

	ep = fwnode_graph_get_next_endpoint(fwnode, NULL);
	if (!ep)
		return -ENXIO;

	ret = v4l2_fwnode_endpoint_alloc_parse(ep, &bus_cfg);
	fwnode_handle_put(ep);
	if (ret)
		return ret;

	if (bus_cfg.bus.mipi_csi2.num_data_lanes != OV8856_DATA_LANES) {
		dev_err(dev, "number of CSI2 data lanes %d is not supported",
			bus_cfg.bus.mipi_csi2.num_data_lanes);
		ret = -EINVAL;
		goto check_hwcfg_error;
	}

	if (!bus_cfg.nr_of_link_frequencies) {
		dev_err(dev, "no link frequencies defined");
		ret = -EINVAL;
		goto check_hwcfg_error;
	}

	for (i = 0; i < ARRAY_SIZE(link_freq_menu_items); i++) {
		for (j = 0; j < bus_cfg.nr_of_link_frequencies; j++) {
			if (link_freq_menu_items[i] ==
				bus_cfg.link_frequencies[j])
				break;
		}

		if (j == bus_cfg.nr_of_link_frequencies) {
			dev_err(dev, "no link frequency %lld supported",
				link_freq_menu_items[i]);
			ret = -EINVAL;
			goto check_hwcfg_error;
		}
	}

check_hwcfg_error:
	v4l2_fwnode_endpoint_free(&bus_cfg);

	return ret;
}