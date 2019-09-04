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
typedef  int u32 ;
struct fapll_data {int /*<<< orphan*/  base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int FAPLL_MAIN_PLLEN ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct fapll_data* to_fapll (struct clk_hw*) ; 

__attribute__((used)) static int ti_fapll_is_enabled(struct clk_hw *hw)
{
	struct fapll_data *fd = to_fapll(hw);
	u32 v = readl_relaxed(fd->base);

	return v & FAPLL_MAIN_PLLEN;
}