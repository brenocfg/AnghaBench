#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ sony_call_snc_handle (int /*<<< orphan*/ ,int,unsigned int*) ; 
 TYPE_1__* tp_ctl ; 

__attribute__((used)) static ssize_t sony_nc_touchpad_store(struct device *dev,
		struct device_attribute *attr, const char *buffer, size_t count)
{
	unsigned int result;
	unsigned long value;

	if (count > 31)
		return -EINVAL;

	if (kstrtoul(buffer, 10, &value) || value > 1)
		return -EINVAL;

	/* sysfs: 0 disabled, 1 enabled
	 * EC: 0 enabled, 1 disabled
	 */
	if (sony_call_snc_handle(tp_ctl->handle,
				(!value << 0x10) | 0x100, &result))
		return -EIO;

	return count;
}