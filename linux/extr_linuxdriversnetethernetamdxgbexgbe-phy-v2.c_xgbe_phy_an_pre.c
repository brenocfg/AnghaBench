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
struct xgbe_prv_data {int an_mode; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int /*<<< orphan*/  cur_mode; } ;

/* Variables and functions */
#define  XGBE_AN_MODE_CL73 129 
#define  XGBE_AN_MODE_CL73_REDRV 128 
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  xgbe_phy_cdr_notrack (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_an_pre(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		if (phy_data->cur_mode != XGBE_MODE_KR)
			break;

		xgbe_phy_cdr_notrack(pdata);
		break;
	default:
		break;
	}
}