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
typedef  int u8 ;
struct clk_sam9260_slow {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int AT91_PMC_OSCSEL ; 
 int /*<<< orphan*/  AT91_PMC_SR ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 struct clk_sam9260_slow* to_clk_sam9260_slow (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_sam9260_slow_get_parent(struct clk_hw *hw)
{
	struct clk_sam9260_slow *slowck = to_clk_sam9260_slow(hw);
	unsigned int status;

	regmap_read(slowck->regmap, AT91_PMC_SR, &status);

	return status & AT91_PMC_OSCSEL ? 1 : 0;
}