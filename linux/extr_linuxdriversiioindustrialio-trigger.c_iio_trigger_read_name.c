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
struct iio_trigger {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct iio_trigger* to_iio_trigger (struct device*) ; 

__attribute__((used)) static ssize_t iio_trigger_read_name(struct device *dev,
				     struct device_attribute *attr,
				     char *buf)
{
	struct iio_trigger *trig = to_iio_trigger(dev);
	return sprintf(buf, "%s\n", trig->name);
}