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
typedef  int /*<<< orphan*/  u8 ;
struct ti_clk_divider {int /*<<< orphan*/  flags; int /*<<< orphan*/  max_div; int /*<<< orphan*/  num_dividers; int /*<<< orphan*/  dividers; } ;
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ti_clk_parse_divider_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct clk_div_table const**) ; 

__attribute__((used)) static const struct clk_div_table *
_get_div_table_from_setup(struct ti_clk_divider *setup, u8 *width)
{
	const struct clk_div_table *table = NULL;

	ti_clk_parse_divider_data(setup->dividers, setup->num_dividers,
				  setup->max_div, setup->flags, width,
				  &table);

	return table;
}