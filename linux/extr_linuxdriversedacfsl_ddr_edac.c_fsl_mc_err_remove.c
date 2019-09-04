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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {struct fsl_mc_pdata* pvt_info; } ;
struct fsl_mc_pdata {scalar_t__ mc_vbase; } ;

/* Variables and functions */
 scalar_t__ EDAC_OPSTATE_INT ; 
 scalar_t__ FSL_MC_ERR_DISABLE ; 
 scalar_t__ FSL_MC_ERR_INT_EN ; 
 scalar_t__ FSL_MC_ERR_SBE ; 
 int /*<<< orphan*/  ddr_out32 (scalar_t__,int /*<<< orphan*/ ) ; 
 struct mem_ctl_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  orig_ddr_err_disable ; 
 int /*<<< orphan*/  orig_ddr_err_sbe ; 

int fsl_mc_err_remove(struct platform_device *op)
{
	struct mem_ctl_info *mci = dev_get_drvdata(&op->dev);
	struct fsl_mc_pdata *pdata = mci->pvt_info;

	edac_dbg(0, "\n");

	if (edac_op_state == EDAC_OPSTATE_INT) {
		ddr_out32(pdata->mc_vbase + FSL_MC_ERR_INT_EN, 0);
	}

	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_DISABLE,
		  orig_ddr_err_disable);
	ddr_out32(pdata->mc_vbase + FSL_MC_ERR_SBE, orig_ddr_err_sbe);

	edac_mc_del_mc(&op->dev);
	edac_mc_free(mci);
	return 0;
}