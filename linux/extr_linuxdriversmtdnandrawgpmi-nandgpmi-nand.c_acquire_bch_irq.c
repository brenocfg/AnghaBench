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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int dummy; } ;
struct gpmi_nand_data {int /*<<< orphan*/  dev; struct platform_device* pdev; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int ENODEV ; 
 char* GPMI_NAND_BCH_INTERRUPT_RES_NAME ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct gpmi_nand_data*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int acquire_bch_irq(struct gpmi_nand_data *this, irq_handler_t irq_h)
{
	struct platform_device *pdev = this->pdev;
	const char *res_name = GPMI_NAND_BCH_INTERRUPT_RES_NAME;
	struct resource *r;
	int err;

	r = platform_get_resource_byname(pdev, IORESOURCE_IRQ, res_name);
	if (!r) {
		dev_err(this->dev, "Can't get resource for %s\n", res_name);
		return -ENODEV;
	}

	err = devm_request_irq(this->dev, r->start, irq_h, 0, res_name, this);
	if (err)
		dev_err(this->dev, "error requesting BCH IRQ\n");

	return err;
}