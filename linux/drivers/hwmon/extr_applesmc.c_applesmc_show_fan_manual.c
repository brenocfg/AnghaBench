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
 int /*<<< orphan*/  FANS_MANUAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int applesmc_read_key (int /*<<< orphan*/ ,int*,int) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int to_index (struct device_attribute*) ; 

__attribute__((used)) static ssize_t applesmc_show_fan_manual(struct device *dev,
			struct device_attribute *attr, char *sysfsbuf)
{
	int ret;
	u16 manual = 0;
	u8 buffer[2];

	ret = applesmc_read_key(FANS_MANUAL, buffer, 2);
	manual = ((buffer[0] << 8 | buffer[1]) >> to_index(attr)) & 0x01;

	if (ret)
		return ret;
	else
		return snprintf(sysfsbuf, PAGE_SIZE, "%d\n", manual);
}