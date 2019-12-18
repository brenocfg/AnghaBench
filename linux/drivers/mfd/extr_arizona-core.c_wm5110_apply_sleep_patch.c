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
struct arizona_sysclk_state {int dummy; } ;
struct arizona {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int arizona_disable_freerun_sysclk (struct arizona*,struct arizona_sysclk_state*) ; 
 int arizona_enable_freerun_sysclk (struct arizona*,struct arizona_sysclk_state*) ; 
 int regmap_multi_reg_write_bypassed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm5110_sleep_patch ; 

__attribute__((used)) static int wm5110_apply_sleep_patch(struct arizona *arizona)
{
	struct arizona_sysclk_state state;
	int err, ret;

	ret = arizona_enable_freerun_sysclk(arizona, &state);
	if (ret)
		return ret;

	ret = regmap_multi_reg_write_bypassed(arizona->regmap,
					      wm5110_sleep_patch,
					      ARRAY_SIZE(wm5110_sleep_patch));

	err = arizona_disable_freerun_sysclk(arizona, &state);

	return ret ?: err;
}