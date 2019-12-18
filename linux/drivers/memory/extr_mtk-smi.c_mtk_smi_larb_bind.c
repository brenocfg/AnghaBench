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
struct mtk_smi_larb_iommu {int /*<<< orphan*/  mmu; struct device* dev; } ;
struct mtk_smi_larb {unsigned int larbid; int /*<<< orphan*/ * mmu; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int MTK_LARB_NR_MAX ; 
 struct mtk_smi_larb* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int
mtk_smi_larb_bind(struct device *dev, struct device *master, void *data)
{
	struct mtk_smi_larb *larb = dev_get_drvdata(dev);
	struct mtk_smi_larb_iommu *larb_mmu = data;
	unsigned int         i;

	for (i = 0; i < MTK_LARB_NR_MAX; i++) {
		if (dev == larb_mmu[i].dev) {
			larb->larbid = i;
			larb->mmu = &larb_mmu[i].mmu;
			return 0;
		}
	}
	return -ENODEV;
}