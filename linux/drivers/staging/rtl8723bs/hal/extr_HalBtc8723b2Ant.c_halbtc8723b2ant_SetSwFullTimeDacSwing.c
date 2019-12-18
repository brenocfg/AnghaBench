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
typedef  int u32 ;
typedef  int /*<<< orphan*/  PBTC_COEXIST ;

/* Variables and functions */
 int /*<<< orphan*/  halbtc8723b2ant_SetDacSwingReg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void halbtc8723b2ant_SetSwFullTimeDacSwing(
	PBTC_COEXIST pBtCoexist, bool bSwDacSwingOn, u32 swDacSwingLvl
)
{
	if (bSwDacSwingOn)
		halbtc8723b2ant_SetDacSwingReg(pBtCoexist, swDacSwingLvl);
	else
		halbtc8723b2ant_SetDacSwingReg(pBtCoexist, 0x18);
}