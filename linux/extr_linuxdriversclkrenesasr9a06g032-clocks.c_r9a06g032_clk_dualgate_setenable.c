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
typedef  size_t u8 ;
struct r9a06g032_clk_dualgate {int /*<<< orphan*/ * gate; int /*<<< orphan*/  clocks; int /*<<< orphan*/  selector; } ;

/* Variables and functions */
 size_t clk_rdesc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r9a06g032_clk_gate_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
r9a06g032_clk_dualgate_setenable(struct r9a06g032_clk_dualgate *g, int enable)
{
	u8 sel_bit = clk_rdesc_get(g->clocks, g->selector);

	/* we always turn off the 'other' gate, regardless */
	r9a06g032_clk_gate_set(g->clocks, &g->gate[!sel_bit], 0);
	r9a06g032_clk_gate_set(g->clocks, &g->gate[sel_bit], enable);

	return 0;
}