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
struct v4l2_fwnode_endpoint {int nr_of_link_frequencies; int /*<<< orphan*/ * link_frequencies; int /*<<< orphan*/  bus_type; } ;
struct imx355_hwcfg {scalar_t__ ext_clk; int nr_of_link_freqs; int /*<<< orphan*/ * link_freqs; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMX355_EXT_CLK ; 
 int /*<<< orphan*/  V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct fwnode_handle* dev_fwnode (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 struct imx355_hwcfg* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct fwnode_handle* fwnode_graph_get_next_endpoint (struct fwnode_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwnode_handle_put (struct fwnode_handle*) ; 
 int fwnode_property_read_u32 (struct fwnode_handle*,char*,scalar_t__*) ; 
 int v4l2_fwnode_endpoint_alloc_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_free (struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static struct imx355_hwcfg *imx355_get_hwcfg(struct device *dev)
{
	struct imx355_hwcfg *cfg;
	struct v4l2_fwnode_endpoint bus_cfg = {
		.bus_type = V4L2_MBUS_CSI2_DPHY
	};
	struct fwnode_handle *ep;
	struct fwnode_handle *fwnode = dev_fwnode(dev);
	unsigned int i;
	int ret;

	if (!fwnode)
		return NULL;

	ep = fwnode_graph_get_next_endpoint(fwnode, NULL);
	if (!ep)
		return NULL;

	ret = v4l2_fwnode_endpoint_alloc_parse(ep, &bus_cfg);
	if (ret)
		goto out_err;

	cfg = devm_kzalloc(dev, sizeof(*cfg), GFP_KERNEL);
	if (!cfg)
		goto out_err;

	ret = fwnode_property_read_u32(dev_fwnode(dev), "clock-frequency",
				       &cfg->ext_clk);
	if (ret) {
		dev_err(dev, "can't get clock frequency");
		goto out_err;
	}

	dev_dbg(dev, "ext clk: %d", cfg->ext_clk);
	if (cfg->ext_clk != IMX355_EXT_CLK) {
		dev_err(dev, "external clock %d is not supported",
			cfg->ext_clk);
		goto out_err;
	}

	dev_dbg(dev, "num of link freqs: %d", bus_cfg.nr_of_link_frequencies);
	if (!bus_cfg.nr_of_link_frequencies) {
		dev_warn(dev, "no link frequencies defined");
		goto out_err;
	}

	cfg->nr_of_link_freqs = bus_cfg.nr_of_link_frequencies;
	cfg->link_freqs = devm_kcalloc(dev,
				       bus_cfg.nr_of_link_frequencies + 1,
				       sizeof(*cfg->link_freqs), GFP_KERNEL);
	if (!cfg->link_freqs)
		goto out_err;

	for (i = 0; i < bus_cfg.nr_of_link_frequencies; i++) {
		cfg->link_freqs[i] = bus_cfg.link_frequencies[i];
		dev_dbg(dev, "link_freq[%d] = %lld", i, cfg->link_freqs[i]);
	}

	v4l2_fwnode_endpoint_free(&bus_cfg);
	fwnode_handle_put(ep);
	return cfg;

out_err:
	v4l2_fwnode_endpoint_free(&bus_cfg);
	fwnode_handle_put(ep);
	return NULL;
}