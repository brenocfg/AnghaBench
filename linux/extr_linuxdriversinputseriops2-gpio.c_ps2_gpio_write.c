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
struct serio {struct ps2_gpio_data* port_data; } ;
struct ps2_gpio_data {int /*<<< orphan*/  tx_mutex; int /*<<< orphan*/  tx_done; } ;

/* Variables and functions */
 int SERIO_TIMEOUT ; 
 int /*<<< orphan*/  __ps2_gpio_write (struct serio*,unsigned char) ; 
 scalar_t__ in_task () ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ps2_gpio_write(struct serio *serio, unsigned char val)
{
	struct ps2_gpio_data *drvdata = serio->port_data;
	int ret = 0;

	if (in_task()) {
		mutex_lock(&drvdata->tx_mutex);
		__ps2_gpio_write(serio, val);
		if (!wait_for_completion_timeout(&drvdata->tx_done,
						 msecs_to_jiffies(10000)))
			ret = SERIO_TIMEOUT;
		mutex_unlock(&drvdata->tx_mutex);
	} else {
		__ps2_gpio_write(serio, val);
	}

	return ret;
}