#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_6__ {int line; } ;
struct tegra_uart_port {int use_rx_pio; int use_tx_pio; int n_adjustable_baud_rates; TYPE_2__* baud_tolerance; int /*<<< orphan*/  enable_modem_interrupt; TYPE_1__ uport; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_7__ {scalar_t__ tolerance; void* upper_range_baud; void* lower_range_baud; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*) ; 
 TYPE_2__* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int of_property_count_u32_elems (struct device_node*,char*) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,void**) ; 

__attribute__((used)) static int tegra_uart_parse_dt(struct platform_device *pdev,
	struct tegra_uart_port *tup)
{
	struct device_node *np = pdev->dev.of_node;
	int port;
	int ret;
	int index;
	u32 pval;
	int count;
	int n_entries;

	port = of_alias_get_id(np, "serial");
	if (port < 0) {
		dev_err(&pdev->dev, "failed to get alias id, errno %d\n", port);
		return port;
	}
	tup->uport.line = port;

	tup->enable_modem_interrupt = of_property_read_bool(np,
					"nvidia,enable-modem-interrupt");

	index = of_property_match_string(np, "dma-names", "rx");
	if (index < 0) {
		tup->use_rx_pio = true;
		dev_info(&pdev->dev, "RX in PIO mode\n");
	}
	index = of_property_match_string(np, "dma-names", "tx");
	if (index < 0) {
		tup->use_tx_pio = true;
		dev_info(&pdev->dev, "TX in PIO mode\n");
	}

	n_entries = of_property_count_u32_elems(np, "nvidia,adjust-baud-rates");
	if (n_entries > 0) {
		tup->n_adjustable_baud_rates = n_entries / 3;
		tup->baud_tolerance =
		devm_kzalloc(&pdev->dev, (tup->n_adjustable_baud_rates) *
			     sizeof(*tup->baud_tolerance), GFP_KERNEL);
		if (!tup->baud_tolerance)
			return -ENOMEM;
		for (count = 0, index = 0; count < n_entries; count += 3,
		     index++) {
			ret =
			of_property_read_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count, &pval);
			if (!ret)
				tup->baud_tolerance[index].lower_range_baud =
				pval;
			ret =
			of_property_read_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count + 1, &pval);
			if (!ret)
				tup->baud_tolerance[index].upper_range_baud =
				pval;
			ret =
			of_property_read_u32_index(np,
						   "nvidia,adjust-baud-rates",
						   count + 2, &pval);
			if (!ret)
				tup->baud_tolerance[index].tolerance =
				(s32)pval;
		}
	} else {
		tup->n_adjustable_baud_rates = 0;
	}

	return 0;
}