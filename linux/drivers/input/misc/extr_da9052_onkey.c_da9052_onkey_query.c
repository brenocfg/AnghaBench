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
struct da9052_onkey {int /*<<< orphan*/  work; int /*<<< orphan*/  input; TYPE_1__* da9052; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA9052_STATUSA_NONKEY ; 
 int /*<<< orphan*/  DA9052_STATUS_A_REG ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int da9052_reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da9052_onkey_query(struct da9052_onkey *onkey)
{
	int ret;

	ret = da9052_reg_read(onkey->da9052, DA9052_STATUS_A_REG);
	if (ret < 0) {
		dev_err(onkey->da9052->dev,
			"Failed to read onkey event err=%d\n", ret);
	} else {
		/*
		 * Since interrupt for deassertion of ONKEY pin is not
		 * generated, onkey event state determines the onkey
		 * button state.
		 */
		bool pressed = !(ret & DA9052_STATUSA_NONKEY);

		input_report_key(onkey->input, KEY_POWER, pressed);
		input_sync(onkey->input);

		/*
		 * Interrupt is generated only when the ONKEY pin
		 * is asserted.  Hence the deassertion of the pin
		 * is simulated through work queue.
		 */
		if (pressed)
			schedule_delayed_work(&onkey->work,
						msecs_to_jiffies(50));
	}
}