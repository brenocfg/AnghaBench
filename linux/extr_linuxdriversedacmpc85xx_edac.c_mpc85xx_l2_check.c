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
typedef  int u32 ;
struct mpc85xx_l2_pdata {scalar_t__ l2_vbase; } ;
struct edac_device_ctl_info {int /*<<< orphan*/  ctl_name; struct mpc85xx_l2_pdata* pvt_info; } ;

/* Variables and functions */
 int L2_EDE_CE_MASK ; 
 int L2_EDE_MASK ; 
 int L2_EDE_UE_MASK ; 
 scalar_t__ MPC85XX_L2_CAPTDATAHI ; 
 scalar_t__ MPC85XX_L2_CAPTDATALO ; 
 scalar_t__ MPC85XX_L2_CAPTECC ; 
 scalar_t__ MPC85XX_L2_ERRADDR ; 
 scalar_t__ MPC85XX_L2_ERRATTR ; 
 scalar_t__ MPC85XX_L2_ERRDET ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int in_be32 (scalar_t__) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static void mpc85xx_l2_check(struct edac_device_ctl_info *edac_dev)
{
	struct mpc85xx_l2_pdata *pdata = edac_dev->pvt_info;
	u32 err_detect;

	err_detect = in_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET);

	if (!(err_detect & L2_EDE_MASK))
		return;

	pr_err("ECC Error in CPU L2 cache\n");
	pr_err("L2 Error Detect Register: 0x%08x\n", err_detect);
	pr_err("L2 Error Capture Data High Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTDATAHI));
	pr_err("L2 Error Capture Data Lo Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTDATALO));
	pr_err("L2 Error Syndrome Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_CAPTECC));
	pr_err("L2 Error Attributes Capture Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRATTR));
	pr_err("L2 Error Address Capture Register: 0x%08x\n",
	       in_be32(pdata->l2_vbase + MPC85XX_L2_ERRADDR));

	/* clear error detect register */
	out_be32(pdata->l2_vbase + MPC85XX_L2_ERRDET, err_detect);

	if (err_detect & L2_EDE_CE_MASK)
		edac_device_handle_ce(edac_dev, 0, 0, edac_dev->ctl_name);

	if (err_detect & L2_EDE_UE_MASK)
		edac_device_handle_ue(edac_dev, 0, 0, edac_dev->ctl_name);
}