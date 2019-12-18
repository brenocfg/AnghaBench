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
struct vmd_dev {int msix_count; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct irq_domain {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  msi_alloc_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct vmd_dev* vmd_from_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmd_msi_prepare(struct irq_domain *domain, struct device *dev,
			   int nvec, msi_alloc_info_t *arg)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct vmd_dev *vmd = vmd_from_bus(pdev->bus);

	if (nvec > vmd->msix_count)
		return vmd->msix_count;

	memset(arg, 0, sizeof(*arg));
	return 0;
}