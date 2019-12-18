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
struct led_classdev {int dummy; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct gb_channel {int is_registered; int /*<<< orphan*/ * led; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct led_classdev* get_channel_cdev (struct gb_channel*) ; 
 struct gb_connection* get_conn_from_channel (struct gb_channel*) ; 
 int led_classdev_register (int /*<<< orphan*/ *,struct led_classdev*) ; 

__attribute__((used)) static int __gb_lights_led_register(struct gb_channel *channel)
{
	struct gb_connection *connection = get_conn_from_channel(channel);
	struct led_classdev *cdev = get_channel_cdev(channel);
	int ret;

	ret = led_classdev_register(&connection->bundle->dev, cdev);
	if (ret < 0)
		channel->led = NULL;
	else
		channel->is_registered = true;
	return ret;
}