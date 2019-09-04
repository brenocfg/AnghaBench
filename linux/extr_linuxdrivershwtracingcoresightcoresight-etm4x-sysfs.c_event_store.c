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
struct etmv4_config {unsigned long eventctrl0; } ;
struct etmv4_drvdata {int nr_event; int /*<<< orphan*/  spinlock; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t event_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t size)
{
	unsigned long val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	if (kstrtoul(buf, 16, &val))
		return -EINVAL;

	spin_lock(&drvdata->spinlock);
	switch (drvdata->nr_event) {
	case 0x0:
		/* EVENT0, bits[7:0] */
		config->eventctrl0 = val & 0xFF;
		break;
	case 0x1:
		 /* EVENT1, bits[15:8] */
		config->eventctrl0 = val & 0xFFFF;
		break;
	case 0x2:
		/* EVENT2, bits[23:16] */
		config->eventctrl0 = val & 0xFFFFFF;
		break;
	case 0x3:
		/* EVENT3, bits[31:24] */
		config->eventctrl0 = val;
		break;
	default:
		break;
	}
	spin_unlock(&drvdata->spinlock);
	return size;
}