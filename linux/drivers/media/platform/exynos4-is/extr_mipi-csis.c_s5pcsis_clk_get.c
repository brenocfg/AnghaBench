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
struct device {int dummy; } ;
struct csis_state {void** clock; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int NUM_CSIS_CLOCKS ; 
 int PTR_ERR (void*) ; 
 void* clk_get (struct device*,int /*<<< orphan*/ ) ; 
 int clk_prepare (void*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/ * csi_clock_name ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5pcsis_clk_put (struct csis_state*) ; 

__attribute__((used)) static int s5pcsis_clk_get(struct csis_state *state)
{
	struct device *dev = &state->pdev->dev;
	int i, ret;

	for (i = 0; i < NUM_CSIS_CLOCKS; i++)
		state->clock[i] = ERR_PTR(-EINVAL);

	for (i = 0; i < NUM_CSIS_CLOCKS; i++) {
		state->clock[i] = clk_get(dev, csi_clock_name[i]);
		if (IS_ERR(state->clock[i])) {
			ret = PTR_ERR(state->clock[i]);
			goto err;
		}
		ret = clk_prepare(state->clock[i]);
		if (ret < 0) {
			clk_put(state->clock[i]);
			state->clock[i] = ERR_PTR(-EINVAL);
			goto err;
		}
	}
	return 0;
err:
	s5pcsis_clk_put(state);
	dev_err(dev, "failed to get clock: %s\n", csi_clock_name[i]);
	return ret;
}