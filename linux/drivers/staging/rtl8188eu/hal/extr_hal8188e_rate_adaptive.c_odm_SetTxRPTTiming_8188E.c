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
typedef  int u8 ;
struct odm_ra_info {scalar_t__ RptTime; } ;
struct odm_dm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__* DynamicTxRPTTiming ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void odm_SetTxRPTTiming_8188E(struct odm_dm_struct *dm_odm,
				     struct odm_ra_info *pRaInfo, u8 extend)
{
	u8 idx = 0;

	for (idx = 0; idx < 5; idx++)
		if (DynamicTxRPTTiming[idx] == pRaInfo->RptTime)
			break;

	if (extend == 0) { /*  back to default timing */
		idx = 0;  /* 200ms */
	} else if (extend == 1) {/*  increase the timing */
		idx += 1;
		if (idx > 5)
			idx = 5;
	} else if (extend == 2) {/*  decrease the timing */
		if (idx != 0)
			idx -= 1;
	}
	pRaInfo->RptTime = DynamicTxRPTTiming[idx];

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("pRaInfo->RptTime = 0x%x\n", pRaInfo->RptTime));
}