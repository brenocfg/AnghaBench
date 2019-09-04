#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ded; int sec; } ;
struct ppc4xx_edac_pdata {TYPE_2__ irqs; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mem_ctl_info {struct ppc4xx_edac_pdata* pvt_info; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INTMAP_ECCDED_INDEX ; 
 int /*<<< orphan*/  INTMAP_ECCSEC_INDEX ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  free_irq (int,struct mem_ctl_info*) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc4xx_edac_isr ; 
 int /*<<< orphan*/  ppc4xx_edac_mc_printk (int /*<<< orphan*/ ,struct mem_ctl_info*,char*,...) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mem_ctl_info*) ; 

__attribute__((used)) static int ppc4xx_edac_register_irq(struct platform_device *op,
				    struct mem_ctl_info *mci)
{
	int status = 0;
	int ded_irq, sec_irq;
	struct ppc4xx_edac_pdata *pdata = mci->pvt_info;
	struct device_node *np = op->dev.of_node;

	ded_irq = irq_of_parse_and_map(np, INTMAP_ECCDED_INDEX);
	sec_irq = irq_of_parse_and_map(np, INTMAP_ECCSEC_INDEX);

	if (!ded_irq || !sec_irq) {
		ppc4xx_edac_mc_printk(KERN_ERR, mci,
				      "Unable to map interrupts.\n");
		status = -ENODEV;
		goto fail;
	}

	status = request_irq(ded_irq,
			     ppc4xx_edac_isr,
			     0,
			     "[EDAC] MC ECCDED",
			     mci);

	if (status < 0) {
		ppc4xx_edac_mc_printk(KERN_ERR, mci,
				      "Unable to request irq %d for ECC DED",
				      ded_irq);
		status = -ENODEV;
		goto fail1;
	}

	status = request_irq(sec_irq,
			     ppc4xx_edac_isr,
			     0,
			     "[EDAC] MC ECCSEC",
			     mci);

	if (status < 0) {
		ppc4xx_edac_mc_printk(KERN_ERR, mci,
				      "Unable to request irq %d for ECC SEC",
				      sec_irq);
		status = -ENODEV;
		goto fail2;
	}

	ppc4xx_edac_mc_printk(KERN_INFO, mci, "ECCDED irq is %d\n", ded_irq);
	ppc4xx_edac_mc_printk(KERN_INFO, mci, "ECCSEC irq is %d\n", sec_irq);

	pdata->irqs.ded = ded_irq;
	pdata->irqs.sec = sec_irq;

	return 0;

 fail2:
	free_irq(sec_irq, mci);

 fail1:
	free_irq(ded_irq, mci);

 fail:
	return status;
}