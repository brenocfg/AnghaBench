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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bd2802_led {int /*<<< orphan*/  rwsem; scalar_t__ adf_on; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct bd2802_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t bd2802_show_adv_conf(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	struct bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));
	ssize_t ret;

	down_read(&led->rwsem);
	if (led->adf_on)
		ret = sprintf(buf, "on\n");
	else
		ret = sprintf(buf, "off\n");
	up_read(&led->rwsem);

	return ret;
}