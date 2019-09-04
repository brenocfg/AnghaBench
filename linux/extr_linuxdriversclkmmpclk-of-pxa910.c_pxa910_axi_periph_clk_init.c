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
struct mmp_clk_unit {int dummy; } ;
struct pxa910_clk_unit {int /*<<< orphan*/  apmu_base; struct mmp_clk_unit unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apmu_div_clks ; 
 int /*<<< orphan*/  apmu_gate_clks ; 
 int /*<<< orphan*/  apmu_mux_clks ; 
 int /*<<< orphan*/  mmp_register_div_clks (struct mmp_clk_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_register_gate_clks (struct mmp_clk_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_register_mux_clks (struct mmp_clk_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pxa910_axi_periph_clk_init(struct pxa910_clk_unit *pxa_unit)
{
	struct mmp_clk_unit *unit = &pxa_unit->unit;

	mmp_register_mux_clks(unit, apmu_mux_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_mux_clks));

	mmp_register_div_clks(unit, apmu_div_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_div_clks));

	mmp_register_gate_clks(unit, apmu_gate_clks, pxa_unit->apmu_base,
				ARRAY_SIZE(apmu_gate_clks));
}