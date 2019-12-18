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
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtol (char const*,int /*<<< orphan*/ ,long*) ; 
 struct device* vexpress_restart_device ; 

__attribute__((used)) static ssize_t vexpress_reset_active_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	long value;
	int err = kstrtol(buf, 0, &value);

	if (!err && value)
		vexpress_restart_device = dev;

	return err ? err : count;
}