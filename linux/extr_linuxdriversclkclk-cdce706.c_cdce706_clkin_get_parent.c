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
struct clk_hw {int dummy; } ;
struct cdce706_hw_data {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct cdce706_hw_data* to_hw_data (struct clk_hw*) ; 

__attribute__((used)) static u8 cdce706_clkin_get_parent(struct clk_hw *hw)
{
	struct cdce706_hw_data *hwd = to_hw_data(hw);

	return hwd->parent;
}