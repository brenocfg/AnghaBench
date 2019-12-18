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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct fsl_elbc_mtd {int /*<<< orphan*/  chip; } ;
struct fsl_elbc_fcm_ctrl {int /*<<< orphan*/  counter; } ;
struct TYPE_2__ {struct fsl_elbc_fcm_ctrl* nand; } ;

/* Variables and functions */
 struct fsl_elbc_mtd* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_elbc_chip_remove (struct fsl_elbc_mtd*) ; 
 int /*<<< orphan*/  fsl_elbc_nand_mutex ; 
 TYPE_1__* fsl_lbc_ctrl_dev ; 
 int /*<<< orphan*/  kfree (struct fsl_elbc_fcm_ctrl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_elbc_nand_remove(struct platform_device *pdev)
{
	struct fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = fsl_lbc_ctrl_dev->nand;
	struct fsl_elbc_mtd *priv = dev_get_drvdata(&pdev->dev);

	nand_release(&priv->chip);
	fsl_elbc_chip_remove(priv);

	mutex_lock(&fsl_elbc_nand_mutex);
	elbc_fcm_ctrl->counter--;
	if (!elbc_fcm_ctrl->counter) {
		fsl_lbc_ctrl_dev->nand = NULL;
		kfree(elbc_fcm_ctrl);
	}
	mutex_unlock(&fsl_elbc_nand_mutex);

	return 0;

}