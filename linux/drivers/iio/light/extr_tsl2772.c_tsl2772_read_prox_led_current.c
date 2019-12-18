#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int prox_power; } ;
struct tsl2772_chip {TYPE_2__* client; TYPE_1__ settings; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct TYPE_5__ {TYPE_3__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int** tsl2772_led_currents ; 

__attribute__((used)) static int tsl2772_read_prox_led_current(struct tsl2772_chip *chip)
{
	struct device_node *of_node = chip->client->dev.of_node;
	int ret, tmp, i;

	ret = of_property_read_u32(of_node, "led-max-microamp", &tmp);
	if (ret < 0)
		return ret;

	for (i = 0; tsl2772_led_currents[i][0] != 0; i++) {
		if (tmp == tsl2772_led_currents[i][0]) {
			chip->settings.prox_power = tsl2772_led_currents[i][1];
			return 0;
		}
	}

	dev_err(&chip->client->dev, "Invalid value %d for led-max-microamp\n",
		tmp);

	return -EINVAL;

}