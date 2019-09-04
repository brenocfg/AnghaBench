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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ reg; } ;
struct socfpga_periph_clk {int fixed_div; int shift; TYPE_1__ hw; scalar_t__ width; scalar_t__ div_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct socfpga_periph_clk* to_socfpga_periph_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_periclk_recalc_rate(struct clk_hw *hwclk,
					     unsigned long parent_rate)
{
	struct socfpga_periph_clk *socfpgaclk = to_socfpga_periph_clk(hwclk);
	u32 div, val;

	if (socfpgaclk->fixed_div) {
		div = socfpgaclk->fixed_div;
	} else {
		if (socfpgaclk->div_reg) {
			val = readl(socfpgaclk->div_reg) >> socfpgaclk->shift;
			val &= GENMASK(socfpgaclk->width - 1, 0);
			parent_rate /= (val + 1);
		}
		div = ((readl(socfpgaclk->hw.reg) & 0x1ff) + 1);
	}

	return parent_rate / div;
}