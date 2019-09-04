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
struct mem_ctl_info {struct fsl_mc_pdata* pvt_info; } ;
struct fsl_mc_pdata {scalar_t__ mc_vbase; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ FSL_MC_DATA_ERR_INJECT_LO ; 
 int ddr_in32 (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct mem_ctl_info* to_mci (struct device*) ; 

__attribute__((used)) static ssize_t fsl_mc_inject_data_lo_show(struct device *dev,
					  struct device_attribute *mattr,
					      char *data)
{
	struct mem_ctl_info *mci = to_mci(dev);
	struct fsl_mc_pdata *pdata = mci->pvt_info;
	return sprintf(data, "0x%08x",
		       ddr_in32(pdata->mc_vbase + FSL_MC_DATA_ERR_INJECT_LO));
}