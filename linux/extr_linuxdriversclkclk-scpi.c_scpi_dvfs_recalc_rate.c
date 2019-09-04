#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scpi_opp {unsigned long freq; } ;
struct scpi_clk {TYPE_2__* info; int /*<<< orphan*/  id; TYPE_1__* scpi_ops; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {struct scpi_opp* opps; } ;
struct TYPE_3__ {int (* dvfs_get_idx ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 
 struct scpi_clk* to_scpi_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long scpi_dvfs_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct scpi_clk *clk = to_scpi_clk(hw);
	int idx = clk->scpi_ops->dvfs_get_idx(clk->id);
	const struct scpi_opp *opp;

	if (idx < 0)
		return 0;

	opp = clk->info->opps + idx;
	return opp->freq;
}