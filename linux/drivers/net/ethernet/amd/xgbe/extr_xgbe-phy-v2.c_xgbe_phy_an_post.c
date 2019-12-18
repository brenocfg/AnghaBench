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
struct xgbe_prv_data {int an_mode; int /*<<< orphan*/  an_result; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {int /*<<< orphan*/  phy_cdr_delay; int /*<<< orphan*/  cur_mode; } ;

/* Variables and functions */
#define  XGBE_AN_COMPLETE 131 
#define  XGBE_AN_MODE_CL73 130 
#define  XGBE_AN_MODE_CL73_REDRV 129 
#define  XGBE_AN_READY 128 
 int /*<<< orphan*/  XGBE_CDR_DELAY_INC ; 
 int /*<<< orphan*/  XGBE_CDR_DELAY_INIT ; 
 int /*<<< orphan*/  XGBE_CDR_DELAY_MAX ; 
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  xgbe_phy_cdr_track (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_phy_an_post(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL73:
	case XGBE_AN_MODE_CL73_REDRV:
		if (phy_data->cur_mode != XGBE_MODE_KR)
			break;

		xgbe_phy_cdr_track(pdata);

		switch (pdata->an_result) {
		case XGBE_AN_READY:
		case XGBE_AN_COMPLETE:
			break;
		default:
			if (phy_data->phy_cdr_delay < XGBE_CDR_DELAY_MAX)
				phy_data->phy_cdr_delay += XGBE_CDR_DELAY_INC;
			else
				phy_data->phy_cdr_delay = XGBE_CDR_DELAY_INIT;
			break;
		}
		break;
	default:
		break;
	}
}