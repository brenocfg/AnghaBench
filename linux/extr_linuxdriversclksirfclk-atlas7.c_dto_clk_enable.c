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
struct clk_hw {int dummy; } ;
struct clk_dto {int src_offset; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int SIRFSOC_CLKC_AUDIO_DTO_ENA ; 
 int SIRFSOC_CLKC_AUDIO_DTO_SRC ; 
 int clkc_readl (int) ; 
 int /*<<< orphan*/  clkc_writel (int,int) ; 
 struct clk_dto* to_dtoclk (struct clk_hw*) ; 

__attribute__((used)) static int dto_clk_enable(struct clk_hw *hw)
{
	u32 val, reg;
	struct clk_dto *clk = to_dtoclk(hw);

	reg = clk->src_offset + SIRFSOC_CLKC_AUDIO_DTO_ENA - SIRFSOC_CLKC_AUDIO_DTO_SRC;

	val = clkc_readl(reg) | BIT(0);
	clkc_writel(val, reg);
	return 0;
}