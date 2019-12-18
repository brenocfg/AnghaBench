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
struct sensor_device_attribute {int index; } ;
struct idt_ntb_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum idt_temp_val { ____Placeholder_idt_temp_val } idt_temp_val ;

/* Variables and functions */
 int /*<<< orphan*/  IDT_TEMP_MAX_MDEG ; 
 int /*<<< orphan*/  IDT_TEMP_MAX_OFFSET ; 
 int /*<<< orphan*/  IDT_TEMP_MIN_MDEG ; 
 int /*<<< orphan*/  IDT_TEMP_MIN_OFFSET ; 
 int IDT_TEMP_OFFSET ; 
 long clamp_val (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct idt_ntb_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  idt_write_temp (struct idt_ntb_dev*,int,long) ; 
 int kstrtol (char const*,int,long*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t idt_sysfs_set_temp(struct device *dev,
				  struct device_attribute *da, const char *buf,
				  size_t count)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct idt_ntb_dev *ndev = dev_get_drvdata(dev);
	enum idt_temp_val type = attr->index;
	long mdeg;
	int ret;

	ret = kstrtol(buf, 10, &mdeg);
	if (ret)
		return ret;

	/* Clamp the passed value in accordance with the type */
	if (type == IDT_TEMP_OFFSET)
		mdeg = clamp_val(mdeg, IDT_TEMP_MIN_OFFSET,
				 IDT_TEMP_MAX_OFFSET);
	else
		mdeg = clamp_val(mdeg, IDT_TEMP_MIN_MDEG, IDT_TEMP_MAX_MDEG);

	idt_write_temp(ndev, type, mdeg);

	return count;
}