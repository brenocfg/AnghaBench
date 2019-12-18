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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  HPWMI_TABLET_MASK ; 
 int hp_wmi_hw_state (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t tablet_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	int value = hp_wmi_hw_state(HPWMI_TABLET_MASK);
	if (value < 0)
		return value;
	return sprintf(buf, "%d\n", value);
}