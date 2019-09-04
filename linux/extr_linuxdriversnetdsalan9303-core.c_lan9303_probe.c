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
struct lan9303 {int /*<<< orphan*/  dev; int /*<<< orphan*/  alr_mutex; int /*<<< orphan*/  indirect_mutex; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int lan9303_check_device (struct lan9303*) ; 
 int /*<<< orphan*/  lan9303_handle_reset (struct lan9303*) ; 
 int lan9303_probe_reset_gpio (struct lan9303*,struct device_node*) ; 
 int lan9303_register_switch (struct lan9303*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int lan9303_probe(struct lan9303 *chip, struct device_node *np)
{
	int ret;

	mutex_init(&chip->indirect_mutex);
	mutex_init(&chip->alr_mutex);

	ret = lan9303_probe_reset_gpio(chip, np);
	if (ret)
		return ret;

	lan9303_handle_reset(chip);

	ret = lan9303_check_device(chip);
	if (ret)
		return ret;

	ret = lan9303_register_switch(chip);
	if (ret) {
		dev_dbg(chip->dev, "Failed to register switch: %d\n", ret);
		return ret;
	}

	return 0;
}