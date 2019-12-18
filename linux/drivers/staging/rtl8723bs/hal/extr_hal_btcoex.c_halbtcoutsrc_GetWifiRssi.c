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
struct TYPE_2__ {int /*<<< orphan*/  EntryMinUndecoratedSmoothedPWDB; } ;
struct hal_com_data {TYPE_1__ dmpriv; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 

__attribute__((used)) static s32 halbtcoutsrc_GetWifiRssi(struct adapter *padapter)
{
	struct hal_com_data *pHalData = GET_HAL_DATA(padapter);

	return pHalData->dmpriv.EntryMinUndecoratedSmoothedPWDB;
}