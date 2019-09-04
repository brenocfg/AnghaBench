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
typedef  scalar_t__ u8 ;
struct clk_hw {int dummy; } ;
struct cdce706_hw_data {scalar_t__ parent; int /*<<< orphan*/  idx; int /*<<< orphan*/  dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDCE706_CLKOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CDCE706_CLKOUT_ENABLE_MASK ; 
 int cdce706_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct cdce706_hw_data* to_hw_data (struct clk_hw*) ; 

__attribute__((used)) static int cdce706_clkout_set_parent(struct clk_hw *hw, u8 index)
{
	struct cdce706_hw_data *hwd = to_hw_data(hw);

	if (hwd->parent == index)
		return 0;
	hwd->parent = index;
	return cdce706_reg_update(hwd->dev_data,
				  CDCE706_CLKOUT(hwd->idx),
				  CDCE706_CLKOUT_ENABLE_MASK, index);
}