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
typedef  char u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  newkey ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_ID_FMT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int applesmc_read_key (char*,char*,int) ; 
 int /*<<< orphan*/  scnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  to_index (struct device_attribute*) ; 

__attribute__((used)) static ssize_t applesmc_show_fan_position(struct device *dev,
				struct device_attribute *attr, char *sysfsbuf)
{
	int ret;
	char newkey[5];
	u8 buffer[17];

	scnprintf(newkey, sizeof(newkey), FAN_ID_FMT, to_index(attr));

	ret = applesmc_read_key(newkey, buffer, 16);
	buffer[16] = 0;

	if (ret)
		return ret;
	else
		return snprintf(sysfsbuf, PAGE_SIZE, "%s\n", buffer+4);
}