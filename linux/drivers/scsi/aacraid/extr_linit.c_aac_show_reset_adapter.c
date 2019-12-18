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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct aac_dev {scalar_t__ in_reset; } ;
typedef  int ssize_t ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int aac_adapter_check_health (struct aac_dev*) ; 
 TYPE_1__* class_to_shost (struct device*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t aac_show_reset_adapter(struct device *device,
				      struct device_attribute *attr,
				      char *buf)
{
	struct aac_dev *dev = (struct aac_dev*)class_to_shost(device)->hostdata;
	int len, tmp;

	tmp = aac_adapter_check_health(dev);
	if ((tmp == 0) && dev->in_reset)
		tmp = -EBUSY;
	len = snprintf(buf, PAGE_SIZE, "0x%x\n", tmp);
	return len;
}