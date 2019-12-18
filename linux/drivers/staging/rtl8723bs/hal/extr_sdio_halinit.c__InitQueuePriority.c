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
struct hal_com_data {int OutEpNumber; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  _InitNormalChipOneOutEpPriority (struct adapter*) ; 
 int /*<<< orphan*/  _InitNormalChipThreeOutEpPriority (struct adapter*) ; 
 int /*<<< orphan*/  _InitNormalChipTwoOutEpPriority (struct adapter*) ; 

__attribute__((used)) static void _InitQueuePriority(struct adapter *Adapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	switch (pHalData->OutEpNumber) {
	case 1:
		_InitNormalChipOneOutEpPriority(Adapter);
		break;
	case 2:
		_InitNormalChipTwoOutEpPriority(Adapter);
		break;
	case 3:
		_InitNormalChipThreeOutEpPriority(Adapter);
		break;
	default:
		/* RT_ASSERT(false, ("Shall not reach here!\n")); */
		break;
	}


}