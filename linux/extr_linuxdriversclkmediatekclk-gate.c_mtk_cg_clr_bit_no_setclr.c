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
struct mtk_clk_gate {int /*<<< orphan*/  sta_ofs; int /*<<< orphan*/  regmap; int /*<<< orphan*/  bit; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_clk_gate* to_mtk_clk_gate (struct clk_hw*) ; 

__attribute__((used)) static void mtk_cg_clr_bit_no_setclr(struct clk_hw *hw)
{
	struct mtk_clk_gate *cg = to_mtk_clk_gate(hw);
	u32 cgbit = BIT(cg->bit);

	regmap_update_bits(cg->regmap, cg->sta_ofs, cgbit, 0);
}