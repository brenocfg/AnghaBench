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
struct arizona_sysclk_state {int /*<<< orphan*/  fll; int /*<<< orphan*/  sysclk; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_FLL1_CONTROL_1 ; 
 int /*<<< orphan*/  ARIZONA_SYSTEM_CLOCK_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_disable_freerun_sysclk(struct arizona *arizona,
					  struct arizona_sysclk_state *state)
{
	int ret;

	ret = regmap_write(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			   state->sysclk);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to re-apply old SYSCLK settings: %d\n", ret);
		return ret;
	}

	ret = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", ret);
		return ret;
	}

	return 0;
}