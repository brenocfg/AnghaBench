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
struct clk_init_data {int /*<<< orphan*/ * parent_names; scalar_t__ num_parents; } ;
struct bcm_clk_sel {scalar_t__ parent_count; int /*<<< orphan*/ * parent_sel; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clk_sel_teardown(struct bcm_clk_sel *sel,
		struct clk_init_data *init_data)
{
	kfree(sel->parent_sel);
	sel->parent_sel = NULL;
	sel->parent_count = 0;

	init_data->num_parents = 0;
	kfree(init_data->parent_names);
	init_data->parent_names = NULL;
}