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
struct clk_utmi {int /*<<< orphan*/  regmap_pmc; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_UCKR ; 
 int /*<<< orphan*/  AT91_PMC_UPLLEN ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_utmi* to_clk_utmi (struct clk_hw*) ; 

__attribute__((used)) static void clk_utmi_unprepare(struct clk_hw *hw)
{
	struct clk_utmi *utmi = to_clk_utmi(hw);

	regmap_update_bits(utmi->regmap_pmc, AT91_CKGR_UCKR,
			   AT91_PMC_UPLLEN, 0);
}