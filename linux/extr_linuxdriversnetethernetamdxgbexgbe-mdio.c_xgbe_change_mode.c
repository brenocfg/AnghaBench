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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;
typedef  enum xgbe_mode { ____Placeholder_xgbe_mode } xgbe_mode ;

/* Variables and functions */
#define  XGBE_MODE_KR 135 
#define  XGBE_MODE_KX_1000 134 
#define  XGBE_MODE_KX_2500 133 
#define  XGBE_MODE_SFI 132 
#define  XGBE_MODE_SGMII_100 131 
#define  XGBE_MODE_SGMII_1000 130 
#define  XGBE_MODE_UNKNOWN 129 
#define  XGBE_MODE_X 128 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xgbe_kr_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_kx_1000_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_kx_2500_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_sfi_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_sgmii_1000_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_sgmii_100_mode (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_x_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_change_mode(struct xgbe_prv_data *pdata,
			     enum xgbe_mode mode)
{
	switch (mode) {
	case XGBE_MODE_KX_1000:
		xgbe_kx_1000_mode(pdata);
		break;
	case XGBE_MODE_KX_2500:
		xgbe_kx_2500_mode(pdata);
		break;
	case XGBE_MODE_KR:
		xgbe_kr_mode(pdata);
		break;
	case XGBE_MODE_SGMII_100:
		xgbe_sgmii_100_mode(pdata);
		break;
	case XGBE_MODE_SGMII_1000:
		xgbe_sgmii_1000_mode(pdata);
		break;
	case XGBE_MODE_X:
		xgbe_x_mode(pdata);
		break;
	case XGBE_MODE_SFI:
		xgbe_sfi_mode(pdata);
		break;
	case XGBE_MODE_UNKNOWN:
		break;
	default:
		netif_dbg(pdata, link, pdata->netdev,
			  "invalid operation mode requested (%u)\n", mode);
	}
}