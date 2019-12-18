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
typedef  int /*<<< orphan*/  u8 ;
struct pca9532_led {int /*<<< orphan*/  id; struct i2c_client* client; } ;
struct pca9532_data {int /*<<< orphan*/  update_lock; TYPE_1__* chip_info; } ;
struct i2c_client {int dummy; } ;
typedef  enum pca9532_state { ____Placeholder_pca9532_state } pca9532_state ;
struct TYPE_2__ {int /*<<< orphan*/  num_leds; } ;

/* Variables and functions */
 int LED_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 char i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum pca9532_state pca9532_getled(struct pca9532_led *led)
{
	struct i2c_client *client = led->client;
	struct pca9532_data *data = i2c_get_clientdata(client);
	u8 maxleds = data->chip_info->num_leds;
	char reg;
	enum pca9532_state ret;

	mutex_lock(&data->update_lock);
	reg = i2c_smbus_read_byte_data(client, LED_REG(maxleds, led->id));
	ret = reg >> LED_NUM(led->id)/2;
	mutex_unlock(&data->update_lock);
	return ret;
}