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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  phy_set_bb_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rFPGA0_XA_HSSIParameter1 ; 
 int /*<<< orphan*/  rFPGA0_XB_HSSIParameter1 ; 

__attribute__((used)) static void pi_mode_switch(struct adapter *adapt, bool pi_mode)
{
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	phy_set_bb_reg(adapt, rFPGA0_XA_HSSIParameter1, bMaskDWord, mode);
	phy_set_bb_reg(adapt, rFPGA0_XB_HSSIParameter1, bMaskDWord, mode);
}