#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int max_hotspot_emergency_temp; int max_edge_emergency_temp; int max_mem_emergency_temp; } ;
struct TYPE_7__ {TYPE_1__ thermal; } ;
struct TYPE_6__ {TYPE_3__ dpm; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_8__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
#define  PP_TEMP_EDGE 130 
#define  PP_TEMP_JUNCTION 129 
 int PP_TEMP_MAX ; 
#define  PP_TEMP_MEM 128 
 struct amdgpu_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t amdgpu_hwmon_show_temp_emergency(struct device *dev,
					     struct device_attribute *attr,
					     char *buf)
{
	struct amdgpu_device *adev = dev_get_drvdata(dev);
	int channel = to_sensor_dev_attr(attr)->index;
	int temp = 0;

	if (channel >= PP_TEMP_MAX)
		return -EINVAL;

	switch (channel) {
	case PP_TEMP_JUNCTION:
		temp = adev->pm.dpm.thermal.max_hotspot_emergency_temp;
		break;
	case PP_TEMP_EDGE:
		temp = adev->pm.dpm.thermal.max_edge_emergency_temp;
		break;
	case PP_TEMP_MEM:
		temp = adev->pm.dpm.thermal.max_mem_emergency_temp;
		break;
	}

	return snprintf(buf, PAGE_SIZE, "%d\n", temp);
}