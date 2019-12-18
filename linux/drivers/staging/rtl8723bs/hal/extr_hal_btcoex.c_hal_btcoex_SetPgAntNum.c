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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  btTotalAntNum; } ;
struct hal_com_data {TYPE_1__ bt_coexist; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_COEX_ANT_TYPE_PG ; 
 int /*<<< orphan*/  EXhalbtcoutsrc_SetAntNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 

void hal_btcoex_SetPgAntNum(struct adapter *padapter, u8 antNum)
{
	struct hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);

	pHalData->bt_coexist.btTotalAntNum = antNum;
	EXhalbtcoutsrc_SetAntNum(BT_COEX_ANT_TYPE_PG, antNum);
}