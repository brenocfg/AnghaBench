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
struct clk_system {int id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_SCER ; 
 int /*<<< orphan*/  clk_system_ready (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  is_pck (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct clk_system* to_clk_system (struct clk_hw*) ; 

__attribute__((used)) static int clk_system_prepare(struct clk_hw *hw)
{
	struct clk_system *sys = to_clk_system(hw);

	regmap_write(sys->regmap, AT91_PMC_SCER, 1 << sys->id);

	if (!is_pck(sys->id))
		return 0;

	while (!clk_system_ready(sys->regmap, sys->id))
		cpu_relax();

	return 0;
}