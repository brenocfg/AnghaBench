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
typedef  int /*<<< orphan*/  u16 ;
struct hal_com_data {int OutEpQueueSel; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  QUEUE_HIGH ; 
 int /*<<< orphan*/  QUEUE_LOW ; 
 int /*<<< orphan*/  QUEUE_NORMAL ; 
#define  TX_SELE_HQ 130 
#define  TX_SELE_LQ 129 
#define  TX_SELE_NQ 128 
 int /*<<< orphan*/  _InitNormalChipRegPriority (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitNormalChipOneOutEpPriority(struct adapter *Adapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	u16 value = 0;
	switch (pHalData->OutEpQueueSel) {
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
		/* RT_ASSERT(false, ("Shall not reach here!\n")); */
		break;
	}

	_InitNormalChipRegPriority(
		Adapter, value, value, value, value, value, value
	);

}