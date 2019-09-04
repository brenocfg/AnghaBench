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
struct isc_clk {int /*<<< orphan*/  parent_id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static u8 isc_clk_get_parent(struct clk_hw *hw)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);

	return isc_clk->parent_id;
}