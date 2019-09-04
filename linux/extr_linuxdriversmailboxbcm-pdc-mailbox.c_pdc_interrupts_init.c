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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct pdc_state {scalar_t__ hw_type; int /*<<< orphan*/  pdc_irq; scalar_t__ pdc_reg_vbase; struct platform_device* pdev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ FA_HW ; 
 scalar_t__ FA_RCVLAZY0_OFFSET ; 
 int /*<<< orphan*/  PDC_INTMASK ; 
 scalar_t__ PDC_INTMASK_OFFSET ; 
 int /*<<< orphan*/  PDC_LAZY_INT ; 
 scalar_t__ PDC_RCVLAZY0_OFFSET ; 
 int PDC_SUCCESS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pdc_state*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_irq_handler ; 

__attribute__((used)) static int pdc_interrupts_init(struct pdc_state *pdcs)
{
	struct platform_device *pdev = pdcs->pdev;
	struct device *dev = &pdev->dev;
	struct device_node *dn = pdev->dev.of_node;
	int err;

	/* interrupt configuration */
	iowrite32(PDC_INTMASK, pdcs->pdc_reg_vbase + PDC_INTMASK_OFFSET);

	if (pdcs->hw_type == FA_HW)
		iowrite32(PDC_LAZY_INT, pdcs->pdc_reg_vbase +
			  FA_RCVLAZY0_OFFSET);
	else
		iowrite32(PDC_LAZY_INT, pdcs->pdc_reg_vbase +
			  PDC_RCVLAZY0_OFFSET);

	/* read irq from device tree */
	pdcs->pdc_irq = irq_of_parse_and_map(dn, 0);
	dev_dbg(dev, "pdc device %s irq %u for pdcs %p",
		dev_name(dev), pdcs->pdc_irq, pdcs);

	err = devm_request_irq(dev, pdcs->pdc_irq, pdc_irq_handler, 0,
			       dev_name(dev), dev);
	if (err) {
		dev_err(dev, "IRQ %u request failed with err %d\n",
			pdcs->pdc_irq, err);
		return err;
	}
	return PDC_SUCCESS;
}