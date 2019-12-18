#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_6__ {scalar_t__ bBtDisableLowPwr; } ;
struct TYPE_7__ {TYPE_1__ btInfo; } ;
typedef  TYPE_2__* PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  halbtcoutsrc_LeaveLowPower (TYPE_2__*) ; 
 int /*<<< orphan*/  halbtcoutsrc_NormalLowPower (TYPE_2__*) ; 

__attribute__((used)) static void halbtcoutsrc_DisableLowPower(PBTC_COEXIST pBtCoexist, u8 bLowPwrDisable)
{
	pBtCoexist->btInfo.bBtDisableLowPwr = bLowPwrDisable;
	if (bLowPwrDisable)
		halbtcoutsrc_LeaveLowPower(pBtCoexist);		/*  leave 32k low power. */
	else
		halbtcoutsrc_NormalLowPower(pBtCoexist);	/*  original 32k low power behavior. */
}