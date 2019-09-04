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
struct mtd_info {struct fsl_elbc_mtd* name; } ;
struct fsl_elbc_mtd {size_t bank; scalar_t__ vbase; int /*<<< orphan*/  chip; TYPE_1__* ctrl; } ;
struct fsl_elbc_fcm_ctrl {int /*<<< orphan*/ ** chips; } ;
struct TYPE_2__ {struct fsl_elbc_fcm_ctrl* nand; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct fsl_elbc_mtd*) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fsl_elbc_chip_remove(struct fsl_elbc_mtd *priv)
{
	struct fsl_elbc_fcm_ctrl *elbc_fcm_ctrl = priv->ctrl->nand;
	struct mtd_info *mtd = nand_to_mtd(&priv->chip);

	kfree(mtd->name);

	if (priv->vbase)
		iounmap(priv->vbase);

	elbc_fcm_ctrl->chips[priv->bank] = NULL;
	kfree(priv);
	return 0;
}