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
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct intel_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BUS_NUM (int) ; 
 int /*<<< orphan*/  device_context_mapped (struct intel_iommu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int domain_context_mapped_cb(struct pci_dev *pdev,
				    u16 alias, void *opaque)
{
	struct intel_iommu *iommu = opaque;

	return !device_context_mapped(iommu, PCI_BUS_NUM(alias), alias & 0xff);
}