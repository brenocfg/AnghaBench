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
struct pca9532_data {int* pwm; int* psc; TYPE_3__* leds; TYPE_1__* chip_info; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;
struct TYPE_5__ {scalar_t__ brightness; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ state; TYPE_2__ ldev; } ;
struct TYPE_4__ {int num_leds; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCA9532_PWM0 ; 
 scalar_t__ PCA9532_TYPE_LED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int,int) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int pca9532_calcpwm(struct i2c_client *client, int pwm, int blink,
	enum led_brightness value)
{
	int a = 0, b = 0, i = 0;
	struct pca9532_data *data = i2c_get_clientdata(client);
	for (i = 0; i < data->chip_info->num_leds; i++) {
		if (data->leds[i].type == PCA9532_TYPE_LED &&
			data->leds[i].state == PCA9532_PWM0+pwm) {
				a++;
				b += data->leds[i].ldev.brightness;
		}
	}
	if (a == 0) {
		dev_err(&client->dev,
		"fear of division by zero %d/%d, wanted %d\n",
			b, a, value);
		return -EINVAL;
	}
	b = b/a;
	if (b > 0xFF)
		return -EINVAL;
	data->pwm[pwm] = b;
	data->psc[pwm] = blink;
	return 0;
}