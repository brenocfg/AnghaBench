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
struct iommu_table {int /*<<< orphan*/  it_kref; int /*<<< orphan*/  it_group_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD_RCU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct iommu_table* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 

struct iommu_table *pnv_pci_table_alloc(int nid)
{
	struct iommu_table *tbl;

	tbl = kzalloc_node(sizeof(struct iommu_table), GFP_KERNEL, nid);
	if (!tbl)
		return NULL;

	INIT_LIST_HEAD_RCU(&tbl->it_group_list);
	kref_init(&tbl->it_kref);

	return tbl;
}