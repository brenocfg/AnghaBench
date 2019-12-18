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
struct s5c73m3 {int /*<<< orphan*/  clock; TYPE_1__* supplies; int /*<<< orphan*/  oif_sd; scalar_t__ isp_ready; scalar_t__ streaming; } ;
struct TYPE_2__ {int /*<<< orphan*/  supply; int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RST ; 
 int S5C73M3_MAX_SUPPLIES ; 
 int /*<<< orphan*/  STBY ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ s5c73m3_gpio_assert (struct s5c73m3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __s5c73m3_power_off(struct s5c73m3 *state)
{
	int i, ret;

	if (s5c73m3_gpio_assert(state, RST))
		usleep_range(10, 50);

	if (s5c73m3_gpio_assert(state, STBY))
		usleep_range(100, 200);

	clk_disable_unprepare(state->clock);

	state->streaming = 0;
	state->isp_ready = 0;

	for (i = S5C73M3_MAX_SUPPLIES - 1; i >= 0; i--) {
		ret = regulator_disable(state->supplies[i].consumer);
		if (ret)
			goto err;
	}

	return 0;
err:
	for (++i; i < S5C73M3_MAX_SUPPLIES; i++) {
		int r = regulator_enable(state->supplies[i].consumer);
		if (r < 0)
			v4l2_err(&state->oif_sd, "Failed to re-enable %s: %d\n",
				 state->supplies[i].supply, r);
	}

	clk_prepare_enable(state->clock);
	return ret;
}