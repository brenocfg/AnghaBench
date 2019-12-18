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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  newkey ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int applesmc_read_key (char*,int*,int) ; 
 int /*<<< orphan*/ * fan_speed_fmt ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  to_index (struct device_attribute*) ; 
 size_t to_option (struct device_attribute*) ; 

__attribute__((used)) static ssize_t applesmc_show_fan_speed(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	int ret;
	unsigned int speed = 0;
	char newkey[5];
	u8 buffer[2];

	scnprintf(newkey, sizeof(newkey), fan_speed_fmt[to_option(attr)],
		  to_index(attr));

	ret = applesmc_read_key(newkey, buffer, 2);
	speed = ((buffer[0] << 8 | buffer[1]) >> 2);

	if (ret)
		return ret;
	else
		return snprintf(sysfsbuf, PAGE_SIZE, "%u\n", speed);
}