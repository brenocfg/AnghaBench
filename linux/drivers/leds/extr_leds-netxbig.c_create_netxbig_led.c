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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct netxbig_led_platform_data {int /*<<< orphan*/  num_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  gpio_ext; } ;
struct TYPE_2__ {int /*<<< orphan*/  groups; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_brightness; int /*<<< orphan*/  brightness; int /*<<< orphan*/  brightness_set; int /*<<< orphan*/  blink_set; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;
struct netxbig_led_data {scalar_t__* mode_val; TYPE_1__ cdev; int /*<<< orphan*/  num_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  bright_addr; int /*<<< orphan*/  mode_addr; scalar_t__ sata; int /*<<< orphan*/  gpio_ext; int /*<<< orphan*/  lock; } ;
struct netxbig_led {scalar_t__* mode_val; int /*<<< orphan*/  bright_addr; int /*<<< orphan*/  mode_addr; int /*<<< orphan*/  bright_max; int /*<<< orphan*/  default_trigger; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  LED_OFF ; 
 scalar_t__ NETXBIG_LED_INVALID_MODE ; 
 size_t NETXBIG_LED_SATA ; 
 int devm_led_classdev_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  netxbig_led_blink_set ; 
 int /*<<< orphan*/  netxbig_led_groups ; 
 int /*<<< orphan*/  netxbig_led_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_netxbig_led(struct platform_device *pdev,
			      struct netxbig_led_platform_data *pdata,
			      struct netxbig_led_data *led_dat,
			      const struct netxbig_led *template)
{
	spin_lock_init(&led_dat->lock);
	led_dat->gpio_ext = pdata->gpio_ext;
	led_dat->cdev.name = template->name;
	led_dat->cdev.default_trigger = template->default_trigger;
	led_dat->cdev.blink_set = netxbig_led_blink_set;
	led_dat->cdev.brightness_set = netxbig_led_set;
	/*
	 * Because the GPIO extension bus don't allow to read registers
	 * value, there is no way to probe the LED initial state.
	 * So, the initial sysfs LED value for the "brightness" and "sata"
	 * attributes are inconsistent.
	 *
	 * Note that the initial LED state can't be reconfigured.
	 * The reason is that the LED behaviour must stay uniform during
	 * the whole boot process (bootloader+linux).
	 */
	led_dat->sata = 0;
	led_dat->cdev.brightness = LED_OFF;
	led_dat->cdev.max_brightness = template->bright_max;
	led_dat->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led_dat->mode_addr = template->mode_addr;
	led_dat->mode_val = template->mode_val;
	led_dat->bright_addr = template->bright_addr;
	led_dat->timer = pdata->timer;
	led_dat->num_timer = pdata->num_timer;
	/*
	 * If available, expose the SATA activity blink capability through
	 * a "sata" sysfs attribute.
	 */
	if (led_dat->mode_val[NETXBIG_LED_SATA] != NETXBIG_LED_INVALID_MODE)
		led_dat->cdev.groups = netxbig_led_groups;

	return devm_led_classdev_register(&pdev->dev, &led_dat->cdev);
}