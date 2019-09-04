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
struct TYPE_2__ {struct clk_init_data* init; } ;
struct sdhci_arasan_data {int /*<<< orphan*/  sdcardclk; TYPE_1__ sdcardclk_hw; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct clk_init_data {char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_GET_RATE_NOCACHE ; 
 char* __clk_get_name (struct clk*) ; 
 int /*<<< orphan*/  arasan_sdcardclk_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_register (struct device*,TYPE_1__*) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_string_index (struct device_node*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sdhci_arasan_register_sdclk(struct sdhci_arasan_data *sdhci_arasan,
				       struct clk *clk_xin,
				       struct device *dev)
{
	struct device_node *np = dev->of_node;
	struct clk_init_data sdcardclk_init;
	const char *parent_clk_name;
	int ret;

	/* Providing a clock to the PHY is optional; no error if missing */
	if (!of_find_property(np, "#clock-cells", NULL))
		return 0;

	ret = of_property_read_string_index(np, "clock-output-names", 0,
					    &sdcardclk_init.name);
	if (ret) {
		dev_err(dev, "DT has #clock-cells but no clock-output-names\n");
		return ret;
	}

	parent_clk_name = __clk_get_name(clk_xin);
	sdcardclk_init.parent_names = &parent_clk_name;
	sdcardclk_init.num_parents = 1;
	sdcardclk_init.flags = CLK_GET_RATE_NOCACHE;
	sdcardclk_init.ops = &arasan_sdcardclk_ops;

	sdhci_arasan->sdcardclk_hw.init = &sdcardclk_init;
	sdhci_arasan->sdcardclk =
		devm_clk_register(dev, &sdhci_arasan->sdcardclk_hw);
	sdhci_arasan->sdcardclk_hw.init = NULL;

	ret = of_clk_add_provider(np, of_clk_src_simple_get,
				  sdhci_arasan->sdcardclk);
	if (ret)
		dev_err(dev, "Failed to add clock provider\n");

	return ret;
}