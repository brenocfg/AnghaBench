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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_mux_core {int /*<<< orphan*/  dev; } ;
struct i2c_arbitrator_data {int wait_free_us; int wait_retry_us; int /*<<< orphan*/  slew_delay_us; int /*<<< orphan*/  our_gpio; int /*<<< orphan*/  their_gpio; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct i2c_arbitrator_data* i2c_mux_priv (struct i2c_mux_core*) ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int i2c_arbitrator_select(struct i2c_mux_core *muxc, u32 chan)
{
	const struct i2c_arbitrator_data *arb = i2c_mux_priv(muxc);
	unsigned long stop_retry, stop_time;

	/* Start a round of trying to claim the bus */
	stop_time = jiffies + usecs_to_jiffies(arb->wait_free_us) + 1;
	do {
		/* Indicate that we want to claim the bus */
		gpiod_set_value(arb->our_gpio, 1);
		udelay(arb->slew_delay_us);

		/* Wait for the other master to release it */
		stop_retry = jiffies + usecs_to_jiffies(arb->wait_retry_us) + 1;
		while (time_before(jiffies, stop_retry)) {
			int gpio_val = gpiod_get_value(arb->their_gpio);

			if (!gpio_val) {
				/* We got it, so return */
				return 0;
			}

			usleep_range(50, 200);
		}

		/* It didn't release, so give up, wait, and try again */
		gpiod_set_value(arb->our_gpio, 0);

		usleep_range(arb->wait_retry_us, arb->wait_retry_us * 2);
	} while (time_before(jiffies, stop_time));

	/* Give up, release our claim */
	gpiod_set_value(arb->our_gpio, 0);
	udelay(arb->slew_delay_us);
	dev_err(muxc->dev, "Could not claim bus, timeout\n");
	return -EBUSY;
}