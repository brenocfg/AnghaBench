#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  bforced_tx20Mhz; } ;
struct rtllib_device {TYPE_1__ bandwidth_auto_switch; struct rt_hi_throughput* pHTInfo; } ;
struct rt_hi_throughput {scalar_t__ bCurTxBW40MHz; scalar_t__ bCurBW40MHz; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
struct cb_desc {int bPacketBW; int data_rate; scalar_t__ bBroadcast; scalar_t__ bMulticast; } ;

/* Variables and functions */

__attribute__((used)) static void rtllib_query_BandwidthMode(struct rtllib_device *ieee,
				       struct cb_desc *tcb_desc)
{
	struct rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	tcb_desc->bPacketBW = false;

	if (!pHTInfo->bCurrentHTSupport || !pHTInfo->bEnableHT)
		return;

	if (tcb_desc->bMulticast || tcb_desc->bBroadcast)
		return;

	if ((tcb_desc->data_rate & 0x80) == 0)
		return;
	if (pHTInfo->bCurBW40MHz && pHTInfo->bCurTxBW40MHz &&
	    !ieee->bandwidth_auto_switch.bforced_tx20Mhz)
		tcb_desc->bPacketBW = true;
}