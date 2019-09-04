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
typedef  int u32 ;
struct ccu_mux_internal {int shift; int width; int* table; } ;
struct ccu_common {int /*<<< orphan*/  hw; scalar_t__ reg; scalar_t__ base; } ;

/* Variables and functions */
 int clk_hw_get_num_parents (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 

u8 ccu_mux_helper_get_parent(struct ccu_common *common,
			     struct ccu_mux_internal *cm)
{
	u32 reg;
	u8 parent;

	reg = readl(common->base + common->reg);
	parent = reg >> cm->shift;
	parent &= (1 << cm->width) - 1;

	if (cm->table) {
		int num_parents = clk_hw_get_num_parents(&common->hw);
		int i;

		for (i = 0; i < num_parents; i++)
			if (cm->table[i] == parent)
				return i;
	}

	return parent;
}