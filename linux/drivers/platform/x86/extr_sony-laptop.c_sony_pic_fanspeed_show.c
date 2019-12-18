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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sony_pic_get_fanspeed (int*) ; 

__attribute__((used)) static ssize_t sony_pic_fanspeed_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	u8 value = 0;
	if (sony_pic_get_fanspeed(&value))
		return -EIO;

	return snprintf(buffer, PAGE_SIZE, "%d\n", value);
}