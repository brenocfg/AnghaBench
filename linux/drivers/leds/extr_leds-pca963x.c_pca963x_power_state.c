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
struct TYPE_4__ {scalar_t__ brightness; } ;
struct pca963x_led {TYPE_1__* chip; int /*<<< orphan*/  led_num; TYPE_2__ led_cdev; } ;
struct TYPE_3__ {unsigned long leds_on; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  PCA963X_MODE1 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static int pca963x_power_state(struct pca963x_led *pca963x)
{
	unsigned long *leds_on = &pca963x->chip->leds_on;
	unsigned long cached_leds = pca963x->chip->leds_on;

	if (pca963x->led_cdev.brightness)
		set_bit(pca963x->led_num, leds_on);
	else
		clear_bit(pca963x->led_num, leds_on);

	if (!(*leds_on) != !cached_leds)
		return i2c_smbus_write_byte_data(pca963x->chip->client,
			PCA963X_MODE1, *leds_on ? 0 : BIT(4));

	return 0;
}