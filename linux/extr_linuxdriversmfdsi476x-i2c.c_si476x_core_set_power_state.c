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
struct si476x_core {scalar_t__ power_state; int /*<<< orphan*/  supplies; TYPE_1__* client; } ;
typedef  enum si476x_power_state { ____Placeholder_si476x_power_state } si476x_power_state ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  SI476X_POWER_DOWN 129 
 scalar_t__ SI476X_POWER_INCONSISTENT ; 
#define  SI476X_POWER_UP_FULL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si476x_core_start (struct si476x_core*,int) ; 
 int si476x_core_stop (struct si476x_core*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int si476x_core_set_power_state(struct si476x_core *core,
				enum si476x_power_state next_state)
{
	/*
	   It is not clear form the datasheet if it is possible to
	   work with device if not all power domains are operational.
	   So for now the power-up policy is "power-up all the things!"
	 */
	int err = 0;

	if (core->power_state == SI476X_POWER_INCONSISTENT) {
		dev_err(&core->client->dev,
			"The device in inconsistent power state\n");
		return -EINVAL;
	}

	if (next_state != core->power_state) {
		switch (next_state) {
		case SI476X_POWER_UP_FULL:
			err = regulator_bulk_enable(ARRAY_SIZE(core->supplies),
						    core->supplies);
			if (err < 0) {
				core->power_state = SI476X_POWER_INCONSISTENT;
				break;
			}
			/*
			 * Startup timing diagram recommends to have a
			 * 100 us delay between enabling of the power
			 * supplies and turning the tuner on.
			 */
			udelay(100);

			err = si476x_core_start(core, false);
			if (err < 0)
				goto disable_regulators;

			core->power_state = next_state;
			break;

		case SI476X_POWER_DOWN:
			core->power_state = next_state;
			err = si476x_core_stop(core, false);
			if (err < 0)
				core->power_state = SI476X_POWER_INCONSISTENT;
disable_regulators:
			err = regulator_bulk_disable(ARRAY_SIZE(core->supplies),
						     core->supplies);
			if (err < 0)
				core->power_state = SI476X_POWER_INCONSISTENT;
			break;
		default:
			BUG();
		}
	}

	return err;
}