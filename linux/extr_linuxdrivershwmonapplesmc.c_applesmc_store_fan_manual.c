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
typedef  int u8 ;
typedef  int u16 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FANS_MANUAL ; 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int applesmc_write_key (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int to_index (struct device_attribute*) ; 

__attribute__((used)) static ssize_t applesmc_store_fan_manual(struct device *dev,
					 struct device_attribute *attr,
					 const char *sysfsbuf, size_t count)
{
	int ret;
	u8 buffer[2];
	unsigned long input;
	u16 val;

	if (kstrtoul(sysfsbuf, 10, &input) < 0)
		return -EINVAL;

	ret = applesmc_read_key(FANS_MANUAL, buffer, 2);
	val = (buffer[0] << 8 | buffer[1]);
	if (ret)
		goto out;

	if (input)
		val = val | (0x01 << to_index(attr));
	else
		val = val & ~(0x01 << to_index(attr));

	buffer[0] = (val >> 8) & 0xFF;
	buffer[1] = val & 0xFF;

	ret = applesmc_write_key(FANS_MANUAL, buffer, 2);

out:
	if (ret)
		return ret;
	else
		return count;
}