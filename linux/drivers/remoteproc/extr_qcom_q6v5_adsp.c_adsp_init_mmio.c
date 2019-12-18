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
struct resource {int /*<<< orphan*/  start; } ;
struct qcom_adsp {int /*<<< orphan*/  halt_lpass; int /*<<< orphan*/  halt_map; TYPE_1__* dev; int /*<<< orphan*/  qdsp6ss_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int adsp_init_mmio(struct qcom_adsp *adsp,
				struct platform_device *pdev)
{
	struct device_node *syscon;
	struct resource *res;
	int ret;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	adsp->qdsp6ss_base = devm_ioremap(&pdev->dev, res->start,
			resource_size(res));
	if (!adsp->qdsp6ss_base) {
		dev_err(adsp->dev, "failed to map QDSP6SS registers\n");
		return -ENOMEM;
	}

	syscon = of_parse_phandle(pdev->dev.of_node, "qcom,halt-regs", 0);
	if (!syscon) {
		dev_err(&pdev->dev, "failed to parse qcom,halt-regs\n");
		return -EINVAL;
	}

	adsp->halt_map = syscon_node_to_regmap(syscon);
	of_node_put(syscon);
	if (IS_ERR(adsp->halt_map))
		return PTR_ERR(adsp->halt_map);

	ret = of_property_read_u32_index(pdev->dev.of_node, "qcom,halt-regs",
			1, &adsp->halt_lpass);
	if (ret < 0) {
		dev_err(&pdev->dev, "no offset in syscon\n");
		return ret;
	}

	return 0;
}