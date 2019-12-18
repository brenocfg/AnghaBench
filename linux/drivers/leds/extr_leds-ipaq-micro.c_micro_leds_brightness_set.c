#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct led_classdev {TYPE_2__* dev; } ;
struct ipaq_micro_msg {int tx_len; int* tx_data; int /*<<< orphan*/  id; } ;
struct ipaq_micro {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int LED_GREEN ; 
 int /*<<< orphan*/  MSG_NOTIFY_LED ; 
 struct ipaq_micro* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int ipaq_micro_tx_msg_sync (struct ipaq_micro*,struct ipaq_micro_msg*) ; 

__attribute__((used)) static int micro_leds_brightness_set(struct led_classdev *led_cdev,
				      enum led_brightness value)
{
	struct ipaq_micro *micro = dev_get_drvdata(led_cdev->dev->parent->parent);
	/*
	 * In this message:
	 * Byte 0 = LED color: 0 = yellow, 1 = green
	 *          yellow LED is always ~30 blinks per minute
	 * Byte 1 = duration (flags?) appears to be ignored
	 * Byte 2 = green ontime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 second
	 * Byte 3 = green offtime in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 seconds
	 */
	struct ipaq_micro_msg msg = {
		.id = MSG_NOTIFY_LED,
		.tx_len = 4,
	};

	msg.tx_data[0] = LED_GREEN;
	msg.tx_data[1] = 0;
	if (value) {
		msg.tx_data[2] = 0; /* Duty cycle 256 */
		msg.tx_data[3] = 1;
	} else {
		msg.tx_data[2] = 1;
		msg.tx_data[3] = 0; /* Duty cycle 256 */
	}
	return ipaq_micro_tx_msg_sync(micro, &msg);
}