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
typedef  int /*<<< orphan*/  u32 ;
struct led_classdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nasgpio_led_set_attr (struct led_classdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nasgpio_gpio_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nasgpio_led_set_attr(struct led_classdev *led_cdev,
				 u32 port, u32 value)
{
	spin_lock(&nasgpio_gpio_lock);
	__nasgpio_led_set_attr(led_cdev, port, value);
	spin_unlock(&nasgpio_gpio_lock);
}