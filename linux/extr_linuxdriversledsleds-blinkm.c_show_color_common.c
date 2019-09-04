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
struct blinkm_data {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLM_GET_CUR_RGB ; 
#define  BLUE 130 
 int EINVAL ; 
#define  GREEN 129 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  RED 128 
 int blinkm_transfer_hw (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct blinkm_data* i2c_get_clientdata (struct i2c_client*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t show_color_common(struct device *dev, char *buf, int color)
{
	struct i2c_client *client;
	struct blinkm_data *data;
	int ret;

	client = to_i2c_client(dev);
	data = i2c_get_clientdata(client);

	ret = blinkm_transfer_hw(client, BLM_GET_CUR_RGB);
	if (ret < 0)
		return ret;
	switch (color) {
	case RED:
		return scnprintf(buf, PAGE_SIZE, "%02X\n", data->red);
	case GREEN:
		return scnprintf(buf, PAGE_SIZE, "%02X\n", data->green);
	case BLUE:
		return scnprintf(buf, PAGE_SIZE, "%02X\n", data->blue);
	default:
		return -EINVAL;
	}
	return -EINVAL;
}