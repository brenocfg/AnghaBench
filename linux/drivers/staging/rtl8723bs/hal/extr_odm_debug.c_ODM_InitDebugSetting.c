#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ DebugComponents; int /*<<< orphan*/  DebugLevel; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_DBG_LOUD ; 

void ODM_InitDebugSetting(PDM_ODM_T pDM_Odm)
{
	pDM_Odm->DebugLevel = ODM_DBG_LOUD;

	pDM_Odm->DebugComponents =
/* BB Functions */
/* 		ODM_COMP_DIG					| */
/* 		ODM_COMP_RA_MASK				| */
/* 		ODM_COMP_DYNAMIC_TXPWR		| */
/* 		ODM_COMP_FA_CNT				| */
/* 		ODM_COMP_RSSI_MONITOR			| */
/* 		ODM_COMP_CCK_PD				| */
/* 		ODM_COMP_ANT_DIV				| */
/* 		ODM_COMP_PWR_SAVE				| */
/* 		ODM_COMP_PWR_TRAIN			| */
/* 		ODM_COMP_RATE_ADAPTIVE		| */
/* 		ODM_COMP_PATH_DIV				| */
/* 		ODM_COMP_DYNAMIC_PRICCA		| */
/* 		ODM_COMP_RXHP					| */
/* 		ODM_COMP_MP					| */
/* 		ODM_COMP_CFO_TRACKING		| */

/* MAC Functions */
/* 		ODM_COMP_EDCA_TURBO			| */
/* 		ODM_COMP_EARLY_MODE			| */
/* RF Functions */
/* 		ODM_COMP_TX_PWR_TRACK		| */
/* 		ODM_COMP_RX_GAIN_TRACK		| */
/* 		ODM_COMP_CALIBRATION			| */
/* Common */
/* 		ODM_COMP_COMMON				| */
/* 		ODM_COMP_INIT					| */
/* 		ODM_COMP_PSD					| */
0;
}