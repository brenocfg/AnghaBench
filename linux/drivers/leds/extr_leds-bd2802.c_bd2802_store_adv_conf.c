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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  bd2802_disable_adv_conf (struct bd2802_led*) ; 
 int /*<<< orphan*/  bd2802_enable_adv_conf (struct bd2802_led*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct bd2802_led* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t bd2802_store_adv_conf(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct bd2802_led *led = i2c_get_clientdata(to_i2c_client(dev));

	if (!count)
		return -EINVAL;

	down_write(&led->rwsem);
	if (!led->adf_on && !strncmp(buf, "on", 2))
		bd2802_enable_adv_conf(led);
	else if (led->adf_on && !strncmp(buf, "off", 3))
		bd2802_disable_adv_conf(led);
	up_write(&led->rwsem);

	return count;
}