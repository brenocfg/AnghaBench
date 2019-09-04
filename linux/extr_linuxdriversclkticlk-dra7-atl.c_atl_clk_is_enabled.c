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
struct dra7_atl_desc {int enabled; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct dra7_atl_desc* to_atl_desc (struct clk_hw*) ; 

__attribute__((used)) static int atl_clk_is_enabled(struct clk_hw *hw)
{
	struct dra7_atl_desc *cdesc = to_atl_desc(hw);

	return cdesc->enabled;
}