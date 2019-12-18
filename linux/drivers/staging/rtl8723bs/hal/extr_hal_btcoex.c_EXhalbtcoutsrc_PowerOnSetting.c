#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int btdmAntNum; } ;
struct TYPE_8__ {TYPE_1__ boardInfo; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  EXhalbtc8723b1ant_PowerOnSetting (TYPE_2__*) ; 
 int /*<<< orphan*/  EXhalbtc8723b2ant_PowerOnSetting (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_IsBtCoexistAvailable (TYPE_2__*) ; 

void EXhalbtcoutsrc_PowerOnSetting(PBTC_COEXIST pBtCoexist)
{
	if (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		return;

	/* Power on setting function is only added in 8723B currently */
	if (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_PowerOnSetting(pBtCoexist);
	else if (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_PowerOnSetting(pBtCoexist);
}