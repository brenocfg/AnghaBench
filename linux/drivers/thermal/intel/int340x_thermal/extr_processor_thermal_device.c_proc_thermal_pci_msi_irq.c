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
struct proc_thermal_device {int /*<<< orphan*/  soc_dts; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  intel_soc_dts_iosf_interrupt_handler (int /*<<< orphan*/ ) ; 
 struct proc_thermal_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static irqreturn_t proc_thermal_pci_msi_irq(int irq, void *devid)
{
	struct proc_thermal_device *proc_priv;
	struct pci_dev *pdev = devid;

	proc_priv = pci_get_drvdata(pdev);

	intel_soc_dts_iosf_interrupt_handler(proc_priv->soc_dts);

	return IRQ_HANDLED;
}