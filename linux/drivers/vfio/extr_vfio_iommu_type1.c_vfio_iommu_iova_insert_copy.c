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
struct list_head {int dummy; } ;
struct vfio_iommu {struct list_head iova_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_splice_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  vfio_iommu_iova_free (struct list_head*) ; 

__attribute__((used)) static void vfio_iommu_iova_insert_copy(struct vfio_iommu *iommu,
					struct list_head *iova_copy)
{
	struct list_head *iova = &iommu->iova_list;

	vfio_iommu_iova_free(iova);

	list_splice_tail(iova_copy, iova);
}