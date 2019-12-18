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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXhalbtcoutsrc_InitCoexDm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXhalbtcoutsrc_InitHwConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLBtCoexist ; 
 int /*<<< orphan*/  hal_btcoex_IsBtExist (struct adapter*) ; 

void hal_btcoex_InitHwConfig(struct adapter *padapter, u8 bWifiOnly)
{
	if (!hal_btcoex_IsBtExist(padapter))
		return;

	EXhalbtcoutsrc_InitHwConfig(&GLBtCoexist, bWifiOnly);
	EXhalbtcoutsrc_InitCoexDm(&GLBtCoexist);
}