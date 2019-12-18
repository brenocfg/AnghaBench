#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ is_msix; } ;
struct msi_desc {TYPE_2__ msi_attrib; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 struct msi_desc* irq_get_msi_desc (unsigned long) ; 
 int kstrtoul (int /*<<< orphan*/ ,int,unsigned long*) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t msi_mode_show(struct device *dev, struct device_attribute *attr,
			     char *buf)
{
	struct msi_desc *entry;
	unsigned long irq;
	int retval;

	retval = kstrtoul(attr->attr.name, 10, &irq);
	if (retval)
		return retval;

	entry = irq_get_msi_desc(irq);
	if (entry)
		return sprintf(buf, "%s\n",
				entry->msi_attrib.is_msix ? "msix" : "msi");

	return -ENODEV;
}