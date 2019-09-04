#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct clk_hw {int dummy; } ;
struct clk_cdce925_pll {int index; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CDCE925_OFFSET_PLL ; 
 int CDCE925_PLL_MUX_OUTPUTS ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 struct clk_cdce925_pll* to_clk_cdce925_pll (struct clk_hw*) ; 

__attribute__((used)) static void cdce925_pll_unprepare(struct clk_hw *hw)
{
	struct clk_cdce925_pll *data = to_clk_cdce925_pll(hw);
	u8 reg_ofs = data->index * CDCE925_OFFSET_PLL;

	regmap_update_bits(data->chip->regmap,
			reg_ofs + CDCE925_PLL_MUX_OUTPUTS, 0x80, 0x80);
}