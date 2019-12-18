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
#define  XGBE_MODE_KR 130 
#define  XGBE_MODE_KX_1000 129 
#define  XGBE_MODE_KX_2500 128 
 int /*<<< orphan*/  xgbe_phy_kr_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_kx_1000_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_kx_2500_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_set_mode(struct xgbe_prv_data *pdata, enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_phy_kx_1000_mode(pdata);
		break;
	case XGBE_MODE_KX_2500:
		xgbe_phy_kx_2500_mode(pdata);
		break;
	case XGBE_MODE_KR:
		xgbe_phy_kr_mode(pdata);
		break;
	default:
		break;
	}
}