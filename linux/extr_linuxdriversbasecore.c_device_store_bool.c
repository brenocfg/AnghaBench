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
struct dev_ext_attribute {int /*<<< orphan*/  var; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ strtobool (char const*,int /*<<< orphan*/ ) ; 
 struct dev_ext_attribute* to_ext_attr (struct device_attribute*) ; 

ssize_t device_store_bool(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t size)
{
	struct dev_ext_attribute *ea = to_ext_attr(attr);

	if (strtobool(buf, ea->var) < 0)
		return -EINVAL;

	return size;
}