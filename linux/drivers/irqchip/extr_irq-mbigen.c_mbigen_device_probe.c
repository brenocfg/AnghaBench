#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_5__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mbigen_device {int /*<<< orphan*/  base; struct platform_device* pdev; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPANION (TYPE_1__*) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbigen_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int mbigen_acpi_create_domain (struct platform_device*,struct mbigen_device*) ; 
 int mbigen_of_create_domain (struct platform_device*,struct mbigen_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mbigen_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int mbigen_device_probe(struct platform_device *pdev)
{
	struct mbigen_device *mgn_chip;
	struct resource *res;
	int err;

	mgn_chip = devm_kzalloc(&pdev->dev, sizeof(*mgn_chip), GFP_KERNEL);
	if (!mgn_chip)
		return -ENOMEM;

	mgn_chip->pdev = pdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;

	mgn_chip->base = devm_ioremap(&pdev->dev, res->start,
				      resource_size(res));
	if (!mgn_chip->base) {
		dev_err(&pdev->dev, "failed to ioremap %pR\n", res);
		return -ENOMEM;
	}

	if (IS_ENABLED(CONFIG_OF) && pdev->dev.of_node)
		err = mbigen_of_create_domain(pdev, mgn_chip);
	else if (ACPI_COMPANION(&pdev->dev))
		err = mbigen_acpi_create_domain(pdev, mgn_chip);
	else
		err = -EINVAL;

	if (err) {
		dev_err(&pdev->dev, "Failed to create mbi-gen irqdomain\n");
		return err;
	}

	platform_set_drvdata(pdev, mgn_chip);
	return 0;
}