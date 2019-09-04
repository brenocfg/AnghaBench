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
struct mtk_smi {int dummy; } ;
struct mtk_smi_larb {struct mtk_smi smi; struct device* smi_common_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_smi_disable (struct mtk_smi*) ; 

void mtk_smi_larb_put(struct device *larbdev)
{
	struct mtk_smi_larb *larb = dev_get_drvdata(larbdev);
	struct mtk_smi *common = dev_get_drvdata(larb->smi_common_dev);

	/*
	 * Don't de-configure the iommu info for this larb since there may be
	 * several modules in this larb.
	 * The iommu info will be reset after power off.
	 */

	mtk_smi_disable(&larb->smi);
	mtk_smi_disable(common);
}