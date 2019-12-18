#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct dw_pcie {TYPE_1__ pp; } ;

/* Variables and functions */
 int dw_pcie_host_init (TYPE_1__*) ; 
 int kirin_pcie_add_msi (struct dw_pcie*,struct platform_device*) ; 
 int /*<<< orphan*/  kirin_pcie_host_ops ; 

__attribute__((used)) static int kirin_add_pcie_port(struct dw_pcie *pci,
			       struct platform_device *pdev)
{
	int ret;

	ret = kirin_pcie_add_msi(pci, pdev);
	if (ret)
		return ret;

	pci->pp.ops = &kirin_pcie_host_ops;

	return dw_pcie_host_init(&pci->pp);
}