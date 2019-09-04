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
 int EBUSY ; 
 int EEXIST ; 
 int MAX_MODULE_HARDRESET_WAIT ; 
 scalar_t__ omap4_prminst_is_hardreset_asserted (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_prminst_rmw_inst_reg_bits (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (scalar_t__,int,int) ; 

int omap4_prminst_deassert_hardreset(u8 shift, u8 st_shift, u8 part, s16 inst,
				     u16 rstctrl_offs, u16 rstst_offs)
{
	int c;
	u32 mask = 1 << shift;
	u32 st_mask = 1 << st_shift;

	/* Check the current status to avoid de-asserting the line twice */
	if (omap4_prminst_is_hardreset_asserted(shift, part, inst,
						rstctrl_offs) == 0)
		return -EEXIST;

	/* Clear the reset status by writing 1 to the status bit */
	omap4_prminst_rmw_inst_reg_bits(0xffffffff, st_mask, part, inst,
					rstst_offs);
	/* de-assert the reset control line */
	omap4_prminst_rmw_inst_reg_bits(mask, 0, part, inst, rstctrl_offs);
	/* wait the status to be set */
	omap_test_timeout(omap4_prminst_is_hardreset_asserted(st_shift, part,
							      inst, rstst_offs),
			  MAX_MODULE_HARDRESET_WAIT, c);

	return (c == MAX_MODULE_HARDRESET_WAIT) ? -EBUSY : 0;
}