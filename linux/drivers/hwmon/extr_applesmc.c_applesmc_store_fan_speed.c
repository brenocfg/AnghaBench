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
typedef  unsigned long u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  newkey ;

/* Variables and functions */
 int EINVAL ; 
 int applesmc_write_key (char*,unsigned long*,int) ; 
 int /*<<< orphan*/ * fan_speed_fmt ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_index (struct device_attribute*) ; 
 size_t to_option (struct device_attribute*) ; 

__attribute__((used)) static ssize_t applesmc_store_fan_speed(struct device *dev,
					struct device_attribute *attr,
					const char *sysfsbuf, size_t count)
{
	int ret;
	unsigned long speed;
	char newkey[5];
	u8 buffer[2];

	if (kstrtoul(sysfsbuf, 10, &speed) < 0 || speed >= 0x4000)
		return -EINVAL;		/* Bigger than a 14-bit value */

	scnprintf(newkey, sizeof(newkey), fan_speed_fmt[to_option(attr)],
		  to_index(attr));

	buffer[0] = (speed >> 6) & 0xff;
	buffer[1] = (speed << 2) & 0xff;
	ret = applesmc_write_key(newkey, buffer, 2);

	if (ret)
		return ret;
	else
		return count;
}