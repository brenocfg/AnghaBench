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
 int clk_utmi_ready (int /*<<< orphan*/ ) ; 
 struct clk_utmi* to_clk_utmi (struct clk_hw*) ; 

__attribute__((used)) static int clk_utmi_is_prepared(struct clk_hw *hw)
{
	struct clk_utmi *utmi = to_clk_utmi(hw);

	return clk_utmi_ready(utmi->regmap_pmc);
}