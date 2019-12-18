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
struct tegra_spi_client_data {int /*<<< orphan*/  rx_clk_tap_delay; int /*<<< orphan*/  tx_clk_tap_delay; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct spi_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 struct tegra_spi_client_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tegra_spi_client_data
	*tegra_spi_parse_cdata_dt(struct spi_device *spi)
{
	struct tegra_spi_client_data *cdata;
	struct device_node *slave_np;

	slave_np = spi->dev.of_node;
	if (!slave_np) {
		dev_dbg(&spi->dev, "device node not found\n");
		return NULL;
	}

	cdata = kzalloc(sizeof(*cdata), GFP_KERNEL);
	if (!cdata)
		return NULL;

	of_property_read_u32(slave_np, "nvidia,tx-clk-tap-delay",
			     &cdata->tx_clk_tap_delay);
	of_property_read_u32(slave_np, "nvidia,rx-clk-tap-delay",
			     &cdata->rx_clk_tap_delay);
	return cdata;
}