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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int* irq_count ; 
 unsigned long irq_first ; 
 int kstrtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned int num_irqs ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_irq(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	unsigned long name;
	unsigned int irq_index;
	int err;

	err = kstrtoul(attr->attr.name, 0, &name);
	if (err)
		return err;

	irq_index = name - irq_first;
	if (irq_index >= num_irqs)
		return -EINVAL;

	return sprintf(buf, "%u\n", irq_count[irq_index]);
}