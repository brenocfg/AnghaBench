#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scpi_clk {int /*<<< orphan*/  id; TYPE_1__* scpi_ops; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* dvfs_set_idx ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int __scpi_find_dvfs_index (struct scpi_clk*,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scpi_clk* to_scpi_clk (struct clk_hw*) ; 

__attribute__((used)) static int scpi_dvfs_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct scpi_clk *clk = to_scpi_clk(hw);
	int ret = __scpi_find_dvfs_index(clk, rate);

	if (ret < 0)
		return ret;
	return clk->scpi_ops->dvfs_set_idx(clk->id, (u8)ret);
}