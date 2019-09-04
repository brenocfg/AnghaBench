#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct clk_init_data* init; } ;
struct scmi_clk {TYPE_2__* info; TYPE_3__ hw; } ;
struct device {int dummy; } ;
struct clk_init_data {int /*<<< orphan*/  name; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct TYPE_6__ {TYPE_1__ range; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_GET_RATE_NOCACHE ; 
 int /*<<< orphan*/  clk_hw_set_rate_range (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  scmi_clk_ops ; 

__attribute__((used)) static int scmi_clk_ops_init(struct device *dev, struct scmi_clk *sclk)
{
	int ret;
	struct clk_init_data init = {
		.flags = CLK_GET_RATE_NOCACHE,
		.num_parents = 0,
		.ops = &scmi_clk_ops,
		.name = sclk->info->name,
	};

	sclk->hw.init = &init;
	ret = devm_clk_hw_register(dev, &sclk->hw);
	if (!ret)
		clk_hw_set_rate_range(&sclk->hw, sclk->info->range.min_rate,
				      sclk->info->range.max_rate);
	return ret;
}