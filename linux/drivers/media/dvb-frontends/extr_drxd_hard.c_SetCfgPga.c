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
typedef  int /*<<< orphan*/  u16 ;
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_HIP_MODE_J_DYNAMIC ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_HIP_MODE_J_STATIC ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_HIP_MODE_J__M ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_HIP__A ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_LOP_MODE_C_DYNAMIC ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_LOP_MODE_C_STATIC ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_LOP_MODE_C__M ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_MODE_LOP__A ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_PGA_MODE_PFN_PCN_AFY_REN ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_PGA_MODE_PFY_PCY_AFY_REN ; 
 int /*<<< orphan*/  B_FE_AG_REG_AG_PGA_MODE__A ; 
 int Read16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int Write16 (struct drxd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int SetCfgPga(struct drxd_state *state, int pgaSwitch)
{
	int status;
	u16 AgModeLop = 0;
	u16 AgModeHip = 0;
	do {
		if (pgaSwitch) {
			/* PGA on */
			/* fine gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			if (status < 0)
				break;
			AgModeLop &= (~(B_FE_AG_REG_AG_MODE_LOP_MODE_C__M));
			AgModeLop |= B_FE_AG_REG_AG_MODE_LOP_MODE_C_DYNAMIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			if (status < 0)
				break;

			/* coarse gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			if (status < 0)
				break;
			AgModeHip &= (~(B_FE_AG_REG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_REG_AG_MODE_HIP_MODE_J_DYNAMIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			if (status < 0)
				break;

			/* enable fine and coarse gain, enable AAF,
			   no ext resistor */
			status = Write16(state, B_FE_AG_REG_AG_PGA_MODE__A, B_FE_AG_REG_AG_PGA_MODE_PFY_PCY_AFY_REN, 0x0000);
			if (status < 0)
				break;
		} else {
			/* PGA off, bypass */

			/* fine gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_LOP__A, &AgModeLop, 0x0000);
			if (status < 0)
				break;
			AgModeLop &= (~(B_FE_AG_REG_AG_MODE_LOP_MODE_C__M));
			AgModeLop |= B_FE_AG_REG_AG_MODE_LOP_MODE_C_STATIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_LOP__A, AgModeLop, 0x0000);
			if (status < 0)
				break;

			/* coarse gain */
			status = Read16(state, B_FE_AG_REG_AG_MODE_HIP__A, &AgModeHip, 0x0000);
			if (status < 0)
				break;
			AgModeHip &= (~(B_FE_AG_REG_AG_MODE_HIP_MODE_J__M));
			AgModeHip |= B_FE_AG_REG_AG_MODE_HIP_MODE_J_STATIC;
			status = Write16(state, B_FE_AG_REG_AG_MODE_HIP__A, AgModeHip, 0x0000);
			if (status < 0)
				break;

			/* disable fine and coarse gain, enable AAF,
			   no ext resistor */
			status = Write16(state, B_FE_AG_REG_AG_PGA_MODE__A, B_FE_AG_REG_AG_PGA_MODE_PFN_PCN_AFY_REN, 0x0000);
			if (status < 0)
				break;
		}
	} while (0);
	return status;
}