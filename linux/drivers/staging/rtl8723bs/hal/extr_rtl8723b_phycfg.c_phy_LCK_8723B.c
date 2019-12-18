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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SetRFReg (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int RF_CHNLBW ; 
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void phy_LCK_8723B(struct adapter *Adapter)
{
	PHY_SetRFReg(Adapter, RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFBE0);
	PHY_SetRFReg(Adapter, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, 0x8C01);
	mdelay(200);
	PHY_SetRFReg(Adapter, RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFFE0);
}