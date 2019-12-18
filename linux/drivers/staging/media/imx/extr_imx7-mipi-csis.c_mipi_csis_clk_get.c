#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct csi_state {unsigned int num_clks; int /*<<< orphan*/  clk_frequency; int /*<<< orphan*/  wrap_clk; TYPE_2__* clks; TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int devm_clk_bulk_get (struct device*,unsigned int,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 TYPE_2__* devm_kcalloc (struct device*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mipi_csis_clk_id ; 

__attribute__((used)) static int mipi_csis_clk_get(struct csi_state *state)
{
	struct device *dev = &state->pdev->dev;
	unsigned int i;
	int ret;

	state->num_clks = ARRAY_SIZE(mipi_csis_clk_id);
	state->clks = devm_kcalloc(dev, state->num_clks, sizeof(*state->clks),
				   GFP_KERNEL);

	if (!state->clks)
		return -ENOMEM;

	for (i = 0; i < state->num_clks; i++)
		state->clks[i].id = mipi_csis_clk_id[i];

	ret = devm_clk_bulk_get(dev, state->num_clks, state->clks);
	if (ret < 0)
		return ret;

	state->wrap_clk = devm_clk_get(dev, "wrap");
	if (IS_ERR(state->wrap_clk))
		return PTR_ERR(state->wrap_clk);

	/* Set clock rate */
	ret = clk_set_rate(state->wrap_clk, state->clk_frequency);
	if (ret < 0)
		dev_err(dev, "set rate=%d failed: %d\n", state->clk_frequency,
			ret);

	return ret;
}