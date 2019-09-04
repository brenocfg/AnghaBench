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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  omap4_prminst_rmw_inst_reg_bits (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int omap4_prminst_assert_hardreset(u8 shift, u8 part, s16 inst,
				   u16 rstctrl_offs)
{
	u32 mask = 1 << shift;

	omap4_prminst_rmw_inst_reg_bits(mask, mask, part, inst, rstctrl_offs);

	return 0;
}