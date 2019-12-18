#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct nand_chip {int /*<<< orphan*/  options; } ;
struct fsmc_nand_data {int bank; int /*<<< orphan*/ * dev_timings; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_SKIP_BBTSCAN ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/ * devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u8_array (struct device_node*,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int fsmc_nand_probe_config_dt(struct platform_device *pdev,
				     struct fsmc_nand_data *host,
				     struct nand_chip *nand)
{
	struct device_node *np = pdev->dev.of_node;
	u32 val;
	int ret;

	nand->options = 0;

	if (!of_property_read_u32(np, "bank-width", &val)) {
		if (val == 2) {
			nand->options |= NAND_BUSWIDTH_16;
		} else if (val != 1) {
			dev_err(&pdev->dev, "invalid bank-width %u\n", val);
			return -EINVAL;
		}
	}

	if (of_get_property(np, "nand-skip-bbtscan", NULL))
		nand->options |= NAND_SKIP_BBTSCAN;

	host->dev_timings = devm_kzalloc(&pdev->dev,
					 sizeof(*host->dev_timings),
					 GFP_KERNEL);
	if (!host->dev_timings)
		return -ENOMEM;

	ret = of_property_read_u8_array(np, "timings", (u8 *)host->dev_timings,
					sizeof(*host->dev_timings));
	if (ret)
		host->dev_timings = NULL;

	/* Set default NAND bank to 0 */
	host->bank = 0;
	if (!of_property_read_u32(np, "bank", &val)) {
		if (val > 3) {
			dev_err(&pdev->dev, "invalid bank %u\n", val);
			return -EINVAL;
		}
		host->bank = val;
	}
	return 0;
}