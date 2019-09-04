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
struct clk_programmable {int /*<<< orphan*/  layout; int /*<<< orphan*/  id; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_PCKR (int /*<<< orphan*/ ) ; 
 unsigned long PROG_PRES (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_programmable* to_clk_programmable (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_programmable_recalc_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct clk_programmable *prog = to_clk_programmable(hw);
	unsigned int pckr;

	regmap_read(prog->regmap, AT91_PMC_PCKR(prog->id), &pckr);

	return parent_rate >> PROG_PRES(prog->layout, pckr);
}