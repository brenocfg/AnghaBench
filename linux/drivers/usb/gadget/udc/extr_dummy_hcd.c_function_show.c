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
struct dummy {TYPE_1__* driver; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct dummy* gadget_dev_to_dummy (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t function_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct dummy	*dum = gadget_dev_to_dummy(dev);

	if (!dum->driver || !dum->driver->function)
		return 0;
	return scnprintf(buf, PAGE_SIZE, "%s\n", dum->driver->function);
}