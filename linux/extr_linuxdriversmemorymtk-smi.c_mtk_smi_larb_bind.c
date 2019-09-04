#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_smi_larb {size_t larbid; int /*<<< orphan*/ * mmu; TYPE_2__* larb_gen; } ;
struct mtk_smi_iommu {unsigned int larb_nr; TYPE_1__* larb_imu; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ need_larbid; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmu; struct device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct mtk_smi_larb* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int
mtk_smi_larb_bind(struct device *dev, struct device *master, void *data)
{
	struct mtk_smi_larb *larb = dev_get_drvdata(dev);
	struct mtk_smi_iommu *smi_iommu = data;
	unsigned int         i;

	if (larb->larb_gen->need_larbid) {
		larb->mmu = &smi_iommu->larb_imu[larb->larbid].mmu;
		return 0;
	}

	/*
	 * If there is no larbid property, Loop to find the corresponding
	 * iommu information.
	 */
	for (i = 0; i < smi_iommu->larb_nr; i++) {
		if (dev == smi_iommu->larb_imu[i].dev) {
			/* The 'mmu' may be updated in iommu-attach/detach. */
			larb->mmu = &smi_iommu->larb_imu[i].mmu;
			return 0;
		}
	}
	return -ENODEV;
}