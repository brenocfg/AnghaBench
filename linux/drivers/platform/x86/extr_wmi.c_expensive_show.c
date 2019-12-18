#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct wmi_block {TYPE_1__ gblock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int ACPI_WMI_EXPENSIVE ; 
 struct wmi_block* dev_to_wblock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t expensive_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct wmi_block *wblock = dev_to_wblock(dev);

	return sprintf(buf, "%d\n",
		       (wblock->gblock.flags & ACPI_WMI_EXPENSIVE) != 0);
}