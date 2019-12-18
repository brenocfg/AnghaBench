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
struct cpcap_led {int powered; int /*<<< orphan*/  dev; int /*<<< orphan*/  vdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_led_set_power(struct cpcap_led *led, bool status)
{
	int err;

	if (status == led->powered)
		return 0;

	if (status)
		err = regulator_enable(led->vdd);
	else
		err = regulator_disable(led->vdd);

	if (err) {
		dev_err(led->dev, "regulator failure: %d", err);
		return err;
	}

	led->powered = status;

	return 0;
}