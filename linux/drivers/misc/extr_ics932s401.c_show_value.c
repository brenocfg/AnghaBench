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
 int BASE_CLOCK ; 
 int /*<<< orphan*/  BUG () ; 
 struct device_attribute dev_attr_ref_clock ; 
 struct device_attribute dev_attr_usb_clock ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_value(struct device *dev,
			  struct device_attribute *devattr,
			  char *buf)
{
	int x;

	if (devattr == &dev_attr_usb_clock)
		x = 48000;
	else if (devattr == &dev_attr_ref_clock)
		x = BASE_CLOCK;
	else
		BUG();

	return sprintf(buf, "%d\n", x);
}