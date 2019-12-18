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
struct rohm_ts_data {int setup2; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int INV_Y ; 
 struct rohm_ts_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t inv_y_show(struct device *dev, struct device_attribute *attr,
			  char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct rohm_ts_data *ts = i2c_get_clientdata(client);

	return sprintf(buf, "%d\n", !!(ts->setup2 & INV_Y));
}