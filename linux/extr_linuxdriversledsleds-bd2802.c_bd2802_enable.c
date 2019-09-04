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
struct bd2802_led {int /*<<< orphan*/  client; } ;
typedef  enum led_ids { ____Placeholder_led_ids } led_ids ;

/* Variables and functions */
 int /*<<< orphan*/  BD2802_REG_CONTROL ; 
 int LED1 ; 
 int LED2 ; 
 int LED_CTL (int,int) ; 
 int /*<<< orphan*/  bd2802_is_led_off (struct bd2802_led*,int) ; 
 int /*<<< orphan*/  bd2802_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bd2802_enable(struct bd2802_led *led, enum led_ids id)
{
	enum led_ids other_led = (id == LED1) ? LED2 : LED1;
	u8 value, other_led_on;

	other_led_on = !bd2802_is_led_off(led, other_led);
	if (id == LED1)
		value = LED_CTL(other_led_on, 1);
	else
		value = LED_CTL(1 , other_led_on);

	bd2802_write_byte(led->client, BD2802_REG_CONTROL, value);
}