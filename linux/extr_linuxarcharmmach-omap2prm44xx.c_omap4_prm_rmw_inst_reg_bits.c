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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  omap4_prm_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_prm_write_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 omap4_prm_rmw_inst_reg_bits(u32 mask, u32 bits, s16 inst, s16 reg)
{
	u32 v;

	v = omap4_prm_read_inst_reg(inst, reg);
	v &= ~mask;
	v |= bits;
	omap4_prm_write_inst_reg(v, inst, reg);

	return v;
}