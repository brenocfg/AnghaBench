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
struct intel_menlow_attribute {int /*<<< orphan*/  handle; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECI_KELVIN_TO_CELSIUS (unsigned long long) ; 
 int sensor_get_auxtrip (int /*<<< orphan*/ ,int,unsigned long long*) ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct intel_menlow_attribute* to_intel_menlow_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t aux_show(struct device *dev, struct device_attribute *dev_attr,
			char *buf, int idx)
{
	struct intel_menlow_attribute *attr = to_intel_menlow_attr(dev_attr);
	unsigned long long value;
	int result;

	result = sensor_get_auxtrip(attr->handle, idx, &value);

	return result ? result : sprintf(buf, "%lu", DECI_KELVIN_TO_CELSIUS(value));
}