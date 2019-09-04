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
struct clk_core {int num_parents; } ;

/* Variables and functions */
 int EINVAL ; 
 struct clk_core* clk_core_get_parent_by_index (struct clk_core*,int) ; 

__attribute__((used)) static int clk_fetch_parent_index(struct clk_core *core,
				  struct clk_core *parent)
{
	int i;

	if (!parent)
		return -EINVAL;

	for (i = 0; i < core->num_parents; i++)
		if (clk_core_get_parent_by_index(core, i) == parent)
			return i;

	return -EINVAL;
}