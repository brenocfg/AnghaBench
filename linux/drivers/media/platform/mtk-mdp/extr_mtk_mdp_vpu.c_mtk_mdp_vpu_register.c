#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct mtk_mdp_dev {TYPE_1__* pdev; int /*<<< orphan*/  vpu_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_MDP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mtk_mdp_vpu_ipi_handler ; 
 struct mtk_mdp_dev* platform_get_drvdata (struct platform_device*) ; 
 int vpu_ipi_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

int mtk_mdp_vpu_register(struct platform_device *pdev)
{
	struct mtk_mdp_dev *mdp = platform_get_drvdata(pdev);
	int err;

	err = vpu_ipi_register(mdp->vpu_dev, IPI_MDP,
			       mtk_mdp_vpu_ipi_handler, "mdp_vpu", NULL);
	if (err)
		dev_err(&mdp->pdev->dev,
			"vpu_ipi_registration fail status=%d\n", err);

	return err;
}