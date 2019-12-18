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
struct thermal_device_info {int direct; scalar_t__ chnl_addr; } ;

/* Variables and functions */
 scalar_t__ ADC_DATA_START_ADDR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int channel_index ; 
 struct thermal_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct thermal_device_info *initialize_sensor(int index)
{
	struct thermal_device_info *td_info =
		kzalloc(sizeof(struct thermal_device_info), GFP_KERNEL);

	if (!td_info)
		return NULL;

	/* Set the base addr of the channel for this sensor */
	td_info->chnl_addr = ADC_DATA_START_ADDR + 2 * (channel_index + index);
	/* Sensor 3 is direct conversion */
	if (index == 3)
		td_info->direct = 1;
	return td_info;
}