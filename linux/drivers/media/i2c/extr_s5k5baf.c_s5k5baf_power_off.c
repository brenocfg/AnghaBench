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
struct s5k5baf {int /*<<< orphan*/  sd; int /*<<< orphan*/  supplies; int /*<<< orphan*/  clock; scalar_t__ apply_crop; scalar_t__ apply_cfg; scalar_t__ streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RST ; 
 int /*<<< orphan*/  S5K5BAF_NUM_SUPPLIES ; 
 int /*<<< orphan*/  STBY ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_gpio_assert (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int s5k5baf_power_off(struct s5k5baf *state)
{
	int ret;

	state->streaming = 0;
	state->apply_cfg = 0;
	state->apply_crop = 0;

	s5k5baf_gpio_assert(state, RST);
	s5k5baf_gpio_assert(state, STBY);

	if (!IS_ERR(state->clock))
		clk_disable_unprepare(state->clock);

	ret = regulator_bulk_disable(S5K5BAF_NUM_SUPPLIES,
					state->supplies);
	if (ret < 0)
		v4l2_err(&state->sd, "failed to disable regulators\n");

	return 0;
}