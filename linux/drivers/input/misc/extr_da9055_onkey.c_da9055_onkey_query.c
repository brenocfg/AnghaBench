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
struct da9055_onkey {int /*<<< orphan*/  work; int /*<<< orphan*/  input; TYPE_1__* da9055; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DA9055_NOKEY_STS ; 
 int /*<<< orphan*/  DA9055_REG_STATUS_A ; 
 int /*<<< orphan*/  KEY_POWER ; 
 int da9055_reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da9055_onkey_query(struct da9055_onkey *onkey)
{
	int key_stat;

	key_stat = da9055_reg_read(onkey->da9055, DA9055_REG_STATUS_A);
	if (key_stat < 0) {
		dev_err(onkey->da9055->dev,
			"Failed to read onkey event %d\n", key_stat);
	} else {
		key_stat &= DA9055_NOKEY_STS;
		/*
		 * Onkey status bit is cleared when onkey button is released.
		 */
		if (!key_stat) {
			input_report_key(onkey->input, KEY_POWER, 0);
			input_sync(onkey->input);
		}
	}

	/*
	 * Interrupt is generated only when the ONKEY pin is asserted.
	 * Hence the deassertion of the pin is simulated through work queue.
	 */
	if (key_stat)
		schedule_delayed_work(&onkey->work, msecs_to_jiffies(10));

}