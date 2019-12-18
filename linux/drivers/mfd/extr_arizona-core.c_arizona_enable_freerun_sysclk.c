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
struct arizona_sysclk_state {int fll; int sysclk; } ;
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_FLL1_CLOCK_OK_STS ; 
 int /*<<< orphan*/  ARIZONA_FLL1_CONTROL_1 ; 
 int ARIZONA_FLL1_ENA ; 
 int ARIZONA_FLL1_FREERUN ; 
 int /*<<< orphan*/  ARIZONA_INTERRUPT_RAW_STATUS_5 ; 
 int /*<<< orphan*/  ARIZONA_SYSTEM_CLOCK_1 ; 
 int arizona_poll_reg (struct arizona*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int arizona_enable_freerun_sysclk(struct arizona *arizona,
					 struct arizona_sysclk_state *state)
{
	int ret, err;

	/* Cache existing FLL and SYSCLK settings */
	ret = regmap_read(arizona->regmap, ARIZONA_FLL1_CONTROL_1, &state->fll);
	if (ret) {
		dev_err(arizona->dev, "Failed to cache FLL settings: %d\n",
			ret);
		return ret;
	}
	ret = regmap_read(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1,
			  &state->sysclk);
	if (ret) {
		dev_err(arizona->dev, "Failed to cache SYSCLK settings: %d\n",
			ret);
		return ret;
	}

	/* Start up SYSCLK using the FLL in free running mode */
	ret = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1,
			ARIZONA_FLL1_ENA | ARIZONA_FLL1_FREERUN);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to start FLL in freerunning mode: %d\n",
			ret);
		return ret;
	}
	ret = arizona_poll_reg(arizona, 180, ARIZONA_INTERRUPT_RAW_STATUS_5,
			       ARIZONA_FLL1_CLOCK_OK_STS,
			       ARIZONA_FLL1_CLOCK_OK_STS);
	if (ret)
		goto err_fll;

	ret = regmap_write(arizona->regmap, ARIZONA_SYSTEM_CLOCK_1, 0x0144);
	if (ret) {
		dev_err(arizona->dev, "Failed to start SYSCLK: %d\n", ret);
		goto err_fll;
	}

	return 0;

err_fll:
	err = regmap_write(arizona->regmap, ARIZONA_FLL1_CONTROL_1, state->fll);
	if (err)
		dev_err(arizona->dev,
			"Failed to re-apply old FLL settings: %d\n", err);

	return ret;
}