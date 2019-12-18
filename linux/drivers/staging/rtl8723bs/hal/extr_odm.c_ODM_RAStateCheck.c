#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {scalar_t__ HighRSSIThresh; scalar_t__ LowRSSIThresh; } ;
struct TYPE_7__ {TYPE_1__ RateAdaptive; } ;
typedef  TYPE_1__* PODM_RATE_ADAPTIVE ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
#define  DM_RATR_STA_HIGH 131 
#define  DM_RATR_STA_INIT 130 
#define  DM_RATR_STA_LOW 129 
#define  DM_RATR_STA_MIDDLE 128 
 int /*<<< orphan*/  ODM_COMP_RA_MASK ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_ASSERT (TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

bool ODM_RAStateCheck(
	PDM_ODM_T pDM_Odm,
	s32 RSSI,
	bool bForceUpdate,
	u8 *pRATRState
)
{
	PODM_RATE_ADAPTIVE pRA = &pDM_Odm->RateAdaptive;
	const u8 GoUpGap = 5;
	u8 HighRSSIThreshForRA = pRA->HighRSSIThresh;
	u8 LowRSSIThreshForRA = pRA->LowRSSIThresh;
	u8 RATRState;

	/*  Threshold Adjustment: */
	/*  when RSSI state trends to go up one or two levels, make sure RSSI is high enough. */
	/*  Here GoUpGap is added to solve the boundary's level alternation issue. */
	switch (*pRATRState) {
	case DM_RATR_STA_INIT:
	case DM_RATR_STA_HIGH:
		break;

	case DM_RATR_STA_MIDDLE:
		HighRSSIThreshForRA += GoUpGap;
		break;

	case DM_RATR_STA_LOW:
		HighRSSIThreshForRA += GoUpGap;
		LowRSSIThreshForRA += GoUpGap;
		break;

	default:
		ODM_RT_ASSERT(pDM_Odm, false, ("wrong rssi level setting %d !", *pRATRState));
		break;
	}

	/*  Decide RATRState by RSSI. */
	if (RSSI > HighRSSIThreshForRA)
		RATRState = DM_RATR_STA_HIGH;
	else if (RSSI > LowRSSIThreshForRA)
		RATRState = DM_RATR_STA_MIDDLE;
	else
		RATRState = DM_RATR_STA_LOW;
	/* printk("==>%s, RATRState:0x%02x , RSSI:%d\n", __func__, RATRState, RSSI); */

	if (*pRATRState != RATRState || bForceUpdate) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_RA_MASK, ODM_DBG_LOUD, ("RSSI Level %d -> %d\n", *pRATRState, RATRState));
		*pRATRState = RATRState;
		return true;
	}

	return false;
}