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
struct xgbe_prv_data {TYPE_1__* vdata; } ;
struct TYPE_2__ {int xpcs_access; } ;

/* Variables and functions */
#define  XGBE_XPCS_ACCESS_V1 129 
#define  XGBE_XPCS_ACCESS_V2 128 
 int xgbe_read_mmd_regs_v1 (struct xgbe_prv_data*,int,int) ; 
 int xgbe_read_mmd_regs_v2 (struct xgbe_prv_data*,int,int) ; 

__attribute__((used)) static int xgbe_read_mmd_regs(struct xgbe_prv_data *pdata, int prtad,
			      int mmd_reg)
{
	switch (pdata->vdata->xpcs_access) {
	case XGBE_XPCS_ACCESS_V1:
		return xgbe_read_mmd_regs_v1(pdata, prtad, mmd_reg);

	case XGBE_XPCS_ACCESS_V2:
	default:
		return xgbe_read_mmd_regs_v2(pdata, prtad, mmd_reg);
	}
}