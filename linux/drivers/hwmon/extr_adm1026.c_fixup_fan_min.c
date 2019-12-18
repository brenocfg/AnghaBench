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
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;
struct adm1026_data {int* fan_div; int* fan_min; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_FAN_MIN (int) ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int clamp_val (int,int,int) ; 
 struct adm1026_data* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void fixup_fan_min(struct device *dev, int fan, int old_div)
{
	struct adm1026_data *data = dev_get_drvdata(dev);
	struct i2c_client *client = data->client;
	int new_min;
	int new_div = data->fan_div[fan];

	/* 0 and 0xff are special.  Don't adjust them */
	if (data->fan_min[fan] == 0 || data->fan_min[fan] == 0xff)
		return;

	new_min = data->fan_min[fan] * old_div / new_div;
	new_min = clamp_val(new_min, 1, 254);
	data->fan_min[fan] = new_min;
	adm1026_write_value(client, ADM1026_REG_FAN_MIN(fan), new_min);
}