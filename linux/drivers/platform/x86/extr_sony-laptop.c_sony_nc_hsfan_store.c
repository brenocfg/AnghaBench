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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 scalar_t__ sony_call_snc_handle (int,unsigned long,unsigned int*) ; 

__attribute__((used)) static ssize_t sony_nc_hsfan_store(struct device *dev,
		struct device_attribute *attr,
		const char *buffer, size_t count)
{
	unsigned int result;
	unsigned long value;

	if (count > 31)
		return -EINVAL;

	if (kstrtoul(buffer, 10, &value) || value > 1)
		return -EINVAL;

	if (sony_call_snc_handle(0x0149, value << 0x10 | 0x0200, &result))
		return -EIO;

	return count;
}