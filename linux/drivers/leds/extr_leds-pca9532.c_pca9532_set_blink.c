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
struct pca9532_led {scalar_t__ state; struct i2c_client* client; } ;
struct led_classdev {int /*<<< orphan*/  brightness; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCA9532_PWM0 ; 
 struct pca9532_led* ldev_to_led (struct led_classdev*) ; 
 int pca9532_calcpwm (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pca9532_setled (struct pca9532_led*) ; 
 int /*<<< orphan*/  pca9532_setpwm (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca9532_set_blink(struct led_classdev *led_cdev,
	unsigned long *delay_on, unsigned long *delay_off)
{
	struct pca9532_led *led = ldev_to_led(led_cdev);
	struct i2c_client *client = led->client;
	int psc;
	int err = 0;

	if (*delay_on == 0 && *delay_off == 0) {
		/* led subsystem ask us for a blink rate */
		*delay_on = 1000;
		*delay_off = 1000;
	}
	if (*delay_on != *delay_off || *delay_on > 1690 || *delay_on < 6)
		return -EINVAL;

	/* Thecus specific: only use PSC/PWM 0 */
	psc = (*delay_on * 152-1)/1000;
	err = pca9532_calcpwm(client, 0, psc, led_cdev->brightness);
	if (err)
		return err;
	if (led->state == PCA9532_PWM0)
		pca9532_setpwm(led->client, 0);
	pca9532_setled(led);

	return 0;
}