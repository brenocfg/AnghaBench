#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct twl6040 {int dummy; } ;
struct TYPE_6__ {struct device* parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int base; int ngpio; int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;

/* Variables and functions */
 scalar_t__ TWL6041_REV_ES2_0 ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct twl6040* dev_get_drvdata (struct device*) ; 
 int devm_gpiochip_add_data (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ twl6040_get_revid (struct twl6040*) ; 
 TYPE_1__ twl6040gpo_chip ; 

__attribute__((used)) static int gpo_twl6040_probe(struct platform_device *pdev)
{
	struct device *twl6040_core_dev = pdev->dev.parent;
	struct twl6040 *twl6040 = dev_get_drvdata(twl6040_core_dev);
	int ret;

	twl6040gpo_chip.base = -1;

	if (twl6040_get_revid(twl6040) < TWL6041_REV_ES2_0)
		twl6040gpo_chip.ngpio = 3; /* twl6040 have 3 GPO */
	else
		twl6040gpo_chip.ngpio = 1; /* twl6041 have 1 GPO */

	twl6040gpo_chip.parent = &pdev->dev;
#ifdef CONFIG_OF_GPIO
	twl6040gpo_chip.of_node = twl6040_core_dev->of_node;
#endif

	ret = devm_gpiochip_add_data(&pdev->dev, &twl6040gpo_chip, NULL);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not register gpiochip, %d\n", ret);
		twl6040gpo_chip.ngpio = 0;
	}

	return ret;
}