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
struct clk_core {size_t num_parents; struct clk_core** parents; int /*<<< orphan*/ * parent_names; } ;

/* Variables and functions */
 struct clk_core* clk_core_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct clk_core *clk_core_get_parent_by_index(struct clk_core *core,
							 u8 index)
{
	if (!core || index >= core->num_parents)
		return NULL;

	if (!core->parents[index])
		core->parents[index] =
				clk_core_lookup(core->parent_names[index]);

	return core->parents[index];
}