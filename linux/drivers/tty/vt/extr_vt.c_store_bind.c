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
struct con_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 struct con_driver* dev_get_drvdata (struct device*) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt_bind (struct con_driver*) ; 
 int /*<<< orphan*/  vt_unbind (struct con_driver*) ; 

__attribute__((used)) static ssize_t store_bind(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct con_driver *con = dev_get_drvdata(dev);
	int bind = simple_strtoul(buf, NULL, 0);

	console_lock();

	if (bind)
		vt_bind(con);
	else
		vt_unbind(con);

	console_unlock();

	return count;
}