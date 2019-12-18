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
struct hideep_ts {int /*<<< orphan*/  vcc_vdd; int /*<<< orphan*/  vcc_vid; scalar_t__ reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hideep_power_off(void *data)
{
	struct hideep_ts *ts = data;

	if (ts->reset_gpio)
		gpiod_set_value(ts->reset_gpio, 1);

	regulator_disable(ts->vcc_vid);
	regulator_disable(ts->vcc_vdd);
}