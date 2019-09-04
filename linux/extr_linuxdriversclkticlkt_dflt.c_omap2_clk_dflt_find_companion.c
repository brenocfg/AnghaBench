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
struct clk_omap_reg {int offset; } ;
struct clk_hw_omap {int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int CM_FCLKEN ; 
 int CM_ICLKEN ; 
 int /*<<< orphan*/  memcpy (struct clk_omap_reg*,int /*<<< orphan*/ *,int) ; 

void omap2_clk_dflt_find_companion(struct clk_hw_omap *clk,
				   struct clk_omap_reg *other_reg,
				   u8 *other_bit)
{
	memcpy(other_reg, &clk->enable_reg, sizeof(*other_reg));

	/*
	 * Convert CM_ICLKEN* <-> CM_FCLKEN*.  This conversion assumes
	 * it's just a matter of XORing the bits.
	 */
	other_reg->offset ^= (CM_FCLKEN ^ CM_ICLKEN);

	*other_bit = clk->enable_bit;
}