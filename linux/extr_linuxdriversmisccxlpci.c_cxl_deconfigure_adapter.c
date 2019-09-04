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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct cxl {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ cxl_is_power9 () ; 
 int /*<<< orphan*/  cxl_native_release_psl_err_irq (struct cxl*) ; 
 int /*<<< orphan*/  cxl_unmap_adapter_regs (struct cxl*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pnv_pci_set_tunnel_bar (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxl_deconfigure_adapter(struct cxl *adapter)
{
	struct pci_dev *pdev = to_pci_dev(adapter->dev.parent);

	if (cxl_is_power9())
		pnv_pci_set_tunnel_bar(pdev, 0x00020000E0000000ull, 0);

	cxl_native_release_psl_err_irq(adapter);
	cxl_unmap_adapter_regs(adapter);

	pci_disable_device(pdev);
}