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
typedef  int /*<<< orphan*/  u16 ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {int OutEpQueueSel; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_HIGH ; 
 int /*<<< orphan*/  QUEUE_LOW ; 
 int /*<<< orphan*/  QUEUE_NORMAL ; 
#define  TX_SELE_HQ 130 
#define  TX_SELE_LQ 129 
#define  TX_SELE_NQ 128 
 int /*<<< orphan*/  _InitNormalChipRegPriority (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitNormalChipOneOutEpPriority(struct adapter *Adapter)
{
	u16 value = 0;

	switch (Adapter->HalData->OutEpQueueSel) {
	case TX_SELE_HQ:
		value = QUEUE_HIGH;
		break;
	case TX_SELE_LQ:
		value = QUEUE_LOW;
		break;
	case TX_SELE_NQ:
		value = QUEUE_NORMAL;
		break;
	default:
		break;
	}
	_InitNormalChipRegPriority(Adapter, value, value, value, value,
				   value, value);
}