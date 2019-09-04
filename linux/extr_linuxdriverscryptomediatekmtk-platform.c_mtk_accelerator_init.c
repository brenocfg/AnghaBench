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
struct mtk_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MTK_IRQ_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mtk_aic_init (struct mtk_cryp*,int) ; 
 int mtk_packet_engine_setup (struct mtk_cryp*) ; 

__attribute__((used)) static int mtk_accelerator_init(struct mtk_cryp *cryp)
{
	int i, err;

	/* Initialize advanced interrupt controller(AIC) */
	for (i = 0; i < MTK_IRQ_NUM; i++) {
		err = mtk_aic_init(cryp, i);
		if (err) {
			dev_err(cryp->dev, "Failed to initialize AIC.\n");
			return err;
		}
	}

	/* Initialize packet engine */
	err = mtk_packet_engine_setup(cryp);
	if (err) {
		dev_err(cryp->dev, "Failed to configure packet engine.\n");
		return err;
	}

	return 0;
}