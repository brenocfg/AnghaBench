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
typedef  int u8 ;
struct twl6040 {int /*<<< orphan*/  audpwron; int /*<<< orphan*/  dev; int /*<<< orphan*/  ready; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int TWL6040_READYINT ; 
 int /*<<< orphan*/  TWL6040_REG_INTID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int twl6040_reg_read (struct twl6040*,int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6040_power_up_automatic(struct twl6040 *twl6040)
{
	int time_left;

	gpio_set_value(twl6040->audpwron, 1);

	time_left = wait_for_completion_timeout(&twl6040->ready,
						msecs_to_jiffies(144));
	if (!time_left) {
		u8 intid;

		dev_warn(twl6040->dev, "timeout waiting for READYINT\n");
		intid = twl6040_reg_read(twl6040, TWL6040_REG_INTID);
		if (!(intid & TWL6040_READYINT)) {
			dev_err(twl6040->dev, "automatic power-up failed\n");
			gpio_set_value(twl6040->audpwron, 0);
			return -ETIMEDOUT;
		}
	}

	return 0;
}