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
struct xgbe_prv_data {int dummy; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  XGBE_MODE_KR 129 
#define  XGBE_MODE_KX_1000 128 
 int xgbe_phy_cur_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_mode xgbe_phy_switch_bp_mode(struct xgbe_prv_data *pdata)
{
	/* If we are in KR switch to KX, and vice-versa */
	switch (xgbe_phy_cur_mode(pdata)) {
	case XGBE_MODE_KX_1000:
		return XGBE_MODE_KR;
	case XGBE_MODE_KR:
	default:
		return XGBE_MODE_KX_1000;
	}
}