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
struct serio {int manual_bind; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 
 struct serio* to_serio_port (struct device*) ; 

__attribute__((used)) static ssize_t serio_set_bind_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct serio *serio = to_serio_port(dev);
	int retval;

	retval = count;
	if (!strncmp(buf, "manual", count)) {
		serio->manual_bind = true;
	} else if (!strncmp(buf, "auto", count)) {
		serio->manual_bind = false;
	} else {
		retval = -EINVAL;
	}

	return retval;
}