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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct iort_pci_alias_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  node; } ;
struct acpi_iort_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORT_IOMMU_TYPE ; 
 int iort_iommu_xlate (int /*<<< orphan*/ ,struct acpi_iort_node*,int /*<<< orphan*/ ) ; 
 struct acpi_iort_node* iort_node_map_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iort_pci_iommu_init(struct pci_dev *pdev, u16 alias, void *data)
{
	struct iort_pci_alias_info *info = data;
	struct acpi_iort_node *parent;
	u32 streamid;

	parent = iort_node_map_id(info->node, alias, &streamid,
				  IORT_IOMMU_TYPE);
	return iort_iommu_xlate(info->dev, parent, streamid);
}