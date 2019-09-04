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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct atmel_smc_nand_controller {int /*<<< orphan*/  base; } ;
struct atmel_nand_controller_caps {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int atmel_nand_controller_add_nands (int /*<<< orphan*/ *) ; 
 int atmel_nand_controller_init (int /*<<< orphan*/ *,struct platform_device*,struct atmel_nand_controller_caps const*) ; 
 int atmel_smc_nand_controller_init (struct atmel_smc_nand_controller*) ; 
 struct atmel_smc_nand_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_smc_nand_controller_probe(struct platform_device *pdev,
				const struct atmel_nand_controller_caps *caps)
{
	struct device *dev = &pdev->dev;
	struct atmel_smc_nand_controller *nc;
	int ret;

	nc = devm_kzalloc(dev, sizeof(*nc), GFP_KERNEL);
	if (!nc)
		return -ENOMEM;

	ret = atmel_nand_controller_init(&nc->base, pdev, caps);
	if (ret)
		return ret;

	ret = atmel_smc_nand_controller_init(nc);
	if (ret)
		return ret;

	return atmel_nand_controller_add_nands(&nc->base);
}