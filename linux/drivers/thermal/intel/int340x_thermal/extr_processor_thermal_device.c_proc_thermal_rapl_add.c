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
struct rapl_mmio_regs {int dummy; } ;
struct proc_thermal_device {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int proc_thermal_rapl_add(struct pci_dev *pdev,
				 struct proc_thermal_device *proc_priv,
				 struct rapl_mmio_regs *rapl_regs)
{
	return 0;
}