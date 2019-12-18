#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* an_post ) (struct xgbe_prv_data*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int an_mode; TYPE_2__ phy_if; } ;

/* Variables and functions */
#define  XGBE_AN_MODE_CL37 131 
#define  XGBE_AN_MODE_CL37_SGMII 130 
#define  XGBE_AN_MODE_CL73 129 
#define  XGBE_AN_MODE_CL73_REDRV 128 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an37_disable (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an73_disable (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_an_disable(struct xgbe_prv_data *pdata)
{
	if (pdata->phy_if.phy_impl.an_post)
		pdata->phy_if.phy_impl.an_post(pdata);

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		xgbe_an73_disable(pdata);
		break;
	case XGBE_AN_MODE_CL37:
	case XGBE_AN_MODE_CL37_SGMII:
		xgbe_an37_disable(pdata);
		break;
	default:
		break;
	}
}