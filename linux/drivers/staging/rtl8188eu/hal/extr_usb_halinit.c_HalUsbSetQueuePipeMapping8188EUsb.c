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
typedef  int u8 ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_2__ {int OutEpNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ConfigNormalChipOutEP_8188E (struct adapter*,int) ; 
 int hal_mapping_out_pipe (struct adapter*,int) ; 

__attribute__((used)) static bool HalUsbSetQueuePipeMapping8188EUsb(struct adapter *adapt, u8 NumInPipe, u8 NumOutPipe)
{
	bool			result		= false;

	_ConfigNormalChipOutEP_8188E(adapt, NumOutPipe);

	/*  Normal chip with one IN and one OUT doesn't have interrupt IN EP. */
	if (adapt->HalData->OutEpNumber == 1) {
		if (NumInPipe != 1)
			return result;
	}

	/*  All config other than above support one Bulk IN and one Interrupt IN. */

	result = hal_mapping_out_pipe(adapt, NumOutPipe);

	return result;
}