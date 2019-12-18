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
struct i2c_mux_core {int dummy; } ;
struct i2c_arbitrator_data {int /*<<< orphan*/  slew_delay_us; int /*<<< orphan*/  our_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_arbitrator_data* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_arbitrator_deselect(struct i2c_mux_core *muxc, u32 chan)
{
	const struct i2c_arbitrator_data *arb = i2c_mux_priv(muxc);

	/* Release the bus and wait for the other master to notice */
	gpiod_set_value(arb->our_gpio, 0);
	udelay(arb->slew_delay_us);

	return 0;
}