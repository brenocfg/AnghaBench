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
struct elants_data {scalar_t__ iap_mode; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ ELAN_IAP_OPERATIONAL ; 
 struct elants_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t show_iap_mode(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct elants_data *ts = i2c_get_clientdata(client);

	return sprintf(buf, "%s\n",
		       ts->iap_mode == ELAN_IAP_OPERATIONAL ?
				"Normal" : "Recovery");
}