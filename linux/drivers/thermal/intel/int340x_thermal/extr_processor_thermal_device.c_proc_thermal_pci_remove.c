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
struct proc_thermal_device {scalar_t__ soc_dts; } ;
struct pci_dev {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct pci_dev*) ; 
 int /*<<< orphan*/  intel_soc_dts_iosf_exit (scalar_t__) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct proc_thermal_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  proc_thermal_rapl_remove () ; 
 int /*<<< orphan*/  proc_thermal_remove (struct proc_thermal_device*) ; 

__attribute__((used)) static void  proc_thermal_pci_remove(struct pci_dev *pdev)
{
	struct proc_thermal_device *proc_priv = pci_get_drvdata(pdev);

	if (proc_priv->soc_dts) {
		intel_soc_dts_iosf_exit(proc_priv->soc_dts);
		if (pdev->irq) {
			free_irq(pdev->irq, pdev);
			pci_disable_msi(pdev);
		}
	}
	proc_thermal_rapl_remove();
	proc_thermal_remove(proc_priv);
}