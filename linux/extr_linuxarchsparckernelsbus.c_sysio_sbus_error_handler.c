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
struct TYPE_3__ {struct iommu* iommu; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; TYPE_1__ archdata; } ;
struct platform_device {TYPE_2__ dev; } ;
struct iommu {int write_complete_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long SYSIO_SBAFSR_MID ; 
 unsigned long SYSIO_SBAFSR_PBERR ; 
 unsigned long SYSIO_SBAFSR_PLE ; 
 unsigned long SYSIO_SBAFSR_PTO ; 
 unsigned long SYSIO_SBAFSR_RD ; 
 unsigned long SYSIO_SBAFSR_SBERR ; 
 unsigned long SYSIO_SBAFSR_SIZE ; 
 unsigned long SYSIO_SBAFSR_SLE ; 
 unsigned long SYSIO_SBAFSR_STO ; 
 unsigned long SYSIO_SBUS_AFAR ; 
 unsigned long SYSIO_SBUS_AFSR ; 
 int of_getintprop_default (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t sysio_sbus_error_handler(int irq, void *dev_id)
{
	struct platform_device *op = dev_id;
	struct iommu *iommu = op->dev.archdata.iommu;
	unsigned long afsr_reg, afar_reg, reg_base;
	unsigned long afsr, afar, error_bits;
	int reported, portid;

	reg_base = iommu->write_complete_reg - 0x2000UL;
	afsr_reg = reg_base + SYSIO_SBUS_AFSR;
	afar_reg = reg_base + SYSIO_SBUS_AFAR;

	afsr = upa_readq(afsr_reg);
	afar = upa_readq(afar_reg);

	/* Clear primary/secondary error status bits. */
	error_bits = afsr &
		(SYSIO_SBAFSR_PLE | SYSIO_SBAFSR_PTO | SYSIO_SBAFSR_PBERR |
		 SYSIO_SBAFSR_SLE | SYSIO_SBAFSR_STO | SYSIO_SBAFSR_SBERR);
	upa_writeq(error_bits, afsr_reg);

	portid = of_getintprop_default(op->dev.of_node, "portid", -1);

	/* Log the error. */
	printk("SYSIO[%x]: SBUS Error, primary error type[%s] read(%d)\n",
	       portid,
	       (((error_bits & SYSIO_SBAFSR_PLE) ?
		 "Late PIO Error" :
		 ((error_bits & SYSIO_SBAFSR_PTO) ?
		  "Time Out" :
		  ((error_bits & SYSIO_SBAFSR_PBERR) ?
		   "Error Ack" : "???")))),
	       (afsr & SYSIO_SBAFSR_RD) ? 1 : 0);
	printk("SYSIO[%x]: size[%lx] MID[%lx]\n",
	       portid,
	       (afsr & SYSIO_SBAFSR_SIZE) >> 42UL,
	       (afsr & SYSIO_SBAFSR_MID) >> 37UL);
	printk("SYSIO[%x]: AFAR[%016lx]\n", portid, afar);
	printk("SYSIO[%x]: Secondary SBUS errors [", portid);
	reported = 0;
	if (afsr & SYSIO_SBAFSR_SLE) {
		reported++;
		printk("(Late PIO Error)");
	}
	if (afsr & SYSIO_SBAFSR_STO) {
		reported++;
		printk("(Time Out)");
	}
	if (afsr & SYSIO_SBAFSR_SBERR) {
		reported++;
		printk("(Error Ack)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	/* XXX check iommu/strbuf for further error status XXX */

	return IRQ_HANDLED;
}