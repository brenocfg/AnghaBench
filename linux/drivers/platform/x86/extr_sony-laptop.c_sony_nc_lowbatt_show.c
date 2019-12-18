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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ sony_call_snc_handle (int,int,unsigned int*) ; 

__attribute__((used)) static ssize_t sony_nc_lowbatt_show(struct device *dev,
		struct device_attribute *attr, char *buffer)
{
	unsigned int result;

	if (sony_call_snc_handle(0x0121, 0x0200, &result))
		return -EIO;

	return snprintf(buffer, PAGE_SIZE, "%d\n", result & 1);
}