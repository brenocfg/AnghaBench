#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sp_pci {int msix_count; TYPE_1__* msix_entry; } ;
struct sp_device {int use_tasklet; int /*<<< orphan*/  ccp_irq; int /*<<< orphan*/  psp_irq; struct device* dev; struct sp_pci* dev_specific; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int entry; int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int pci_enable_msix_range (struct pci_dev*,TYPE_1__*,int,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int sp_get_msix_irqs(struct sp_device *sp)
{
	struct sp_pci *sp_pci = sp->dev_specific;
	struct device *dev = sp->dev;
	struct pci_dev *pdev = to_pci_dev(dev);
	int v, ret;

	for (v = 0; v < ARRAY_SIZE(sp_pci->msix_entry); v++)
		sp_pci->msix_entry[v].entry = v;

	ret = pci_enable_msix_range(pdev, sp_pci->msix_entry, 1, v);
	if (ret < 0)
		return ret;

	sp_pci->msix_count = ret;
	sp->use_tasklet = true;

	sp->psp_irq = sp_pci->msix_entry[0].vector;
	sp->ccp_irq = (sp_pci->msix_count > 1) ? sp_pci->msix_entry[1].vector
					       : sp_pci->msix_entry[0].vector;
	return 0;
}