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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct geni_wrapper {TYPE_1__* ahb_clks; int /*<<< orphan*/  base; struct device* dev; } ;
struct TYPE_2__ {char* id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_AHB_CLKS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct geni_wrapper*) ; 
 int devm_clk_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct geni_wrapper* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (struct device*) ; 
 int /*<<< orphan*/  has_acpi_companion (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int geni_se_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct geni_wrapper *wrapper;
	int ret;

	wrapper = devm_kzalloc(dev, sizeof(*wrapper), GFP_KERNEL);
	if (!wrapper)
		return -ENOMEM;

	wrapper->dev = dev;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wrapper->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(wrapper->base))
		return PTR_ERR(wrapper->base);

	if (!has_acpi_companion(&pdev->dev)) {
		wrapper->ahb_clks[0].id = "m-ahb";
		wrapper->ahb_clks[1].id = "s-ahb";
		ret = devm_clk_bulk_get(dev, NUM_AHB_CLKS, wrapper->ahb_clks);
		if (ret) {
			dev_err(dev, "Err getting AHB clks %d\n", ret);
			return ret;
		}
	}

	dev_set_drvdata(dev, wrapper);
	dev_dbg(dev, "GENI SE Driver probed\n");
	return devm_of_platform_populate(dev);
}