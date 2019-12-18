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
struct rtllib_device {struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {int bCurBW40MHz; scalar_t__ bCurShortGI20MHz; scalar_t__ bCurShortGI40MHz; scalar_t__ bForcedShortGI; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
struct cb_desc {int bUseShortGI; } ;

/* Variables and functions */

__attribute__((used)) static void rtllib_query_HTCapShortGI(struct rtllib_device *ieee,
				      struct cb_desc *tcb_desc)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	tcb_desc->bUseShortGI		= false;

	if (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		return;

	if (pHTInfo->bForcedShortGI) {
		tcb_desc->bUseShortGI = true;
		return;
	}

	if ((pHTInfo->bCurBW40MHz == true) && pHTInfo->bCurShortGI40MHz)
		tcb_desc->bUseShortGI = true;
	else if ((pHTInfo->bCurBW40MHz == false) && pHTInfo->bCurShortGI20MHz)
		tcb_desc->bUseShortGI = true;
}