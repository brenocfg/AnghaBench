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
struct mtk_smi_larb_gen {int /*<<< orphan*/  (* config_port ) (struct device*) ;} ;
struct mtk_smi {int dummy; } ;
struct mtk_smi_larb {struct mtk_smi smi; struct device* smi_common_dev; struct mtk_smi_larb_gen* larb_gen; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mtk_smi_disable (struct mtk_smi*) ; 
 int mtk_smi_enable (struct mtk_smi*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

int mtk_smi_larb_get(struct device *larbdev)
{
	struct mtk_smi_larb *larb = dev_get_drvdata(larbdev);
	const struct mtk_smi_larb_gen *larb_gen = larb->larb_gen;
	struct mtk_smi *common = dev_get_drvdata(larb->smi_common_dev);
	int ret;

	/* Enable the smi-common's power and clocks */
	ret = mtk_smi_enable(common);
	if (ret)
		return ret;

	/* Enable the larb's power and clocks */
	ret = mtk_smi_enable(&larb->smi);
	if (ret) {
		mtk_smi_disable(common);
		return ret;
	}

	/* Configure the iommu info for this larb */
	larb_gen->config_port(larbdev);

	return 0;
}