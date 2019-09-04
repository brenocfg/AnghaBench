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
typedef  scalar_t__ u32 ;
struct bcm_clk_sel {scalar_t__ parent_count; size_t* parent_sel; } ;

/* Variables and functions */
 size_t BAD_CLK_INDEX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ U8_MAX ; 

__attribute__((used)) static u8 parent_index(struct bcm_clk_sel *sel, u8 parent_sel)
{
	u8 i;

	BUG_ON(sel->parent_count > (u32)U8_MAX);
	for (i = 0; i < sel->parent_count; i++)
		if (sel->parent_sel[i] == parent_sel)
			return i;
	return BAD_CLK_INDEX;
}