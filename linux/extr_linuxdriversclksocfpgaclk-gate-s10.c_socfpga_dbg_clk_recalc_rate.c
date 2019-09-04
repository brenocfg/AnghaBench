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
struct socfpga_gate_clk {int shift; scalar_t__ width; int /*<<< orphan*/  div_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct socfpga_gate_clk* to_socfpga_gate_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long socfpga_dbg_clk_recalc_rate(struct clk_hw *hwclk,
						  unsigned long parent_rate)
{
	struct socfpga_gate_clk *socfpgaclk = to_socfpga_gate_clk(hwclk);
	u32 div = 1, val;

	val = readl(socfpgaclk->div_reg) >> socfpgaclk->shift;
	val &= GENMASK(socfpgaclk->width - 1, 0);
	div = (1 << val);
	div = div ? 4 : 1;

	return parent_rate / div;
}