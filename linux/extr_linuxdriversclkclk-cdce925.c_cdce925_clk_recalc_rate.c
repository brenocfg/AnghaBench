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
struct clk_hw {int dummy; } ;
struct clk_cdce925_output {int pdiv; } ;

/* Variables and functions */
 struct clk_cdce925_output* to_clk_cdce925_output (struct clk_hw*) ; 

__attribute__((used)) static unsigned long cdce925_clk_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_cdce925_output *data = to_clk_cdce925_output(hw);

	if (data->pdiv)
		return parent_rate / data->pdiv;
	return 0;
}