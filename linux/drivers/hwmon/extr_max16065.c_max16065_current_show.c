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
struct max16065_data {scalar_t__ curr_sense; int /*<<< orphan*/  curr_gain; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ADC_TO_CURR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct max16065_data* max16065_update_device (struct device*) ; 
 scalar_t__ snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t max16065_current_show(struct device *dev,
				     struct device_attribute *da, char *buf)
{
	struct max16065_data *data = max16065_update_device(dev);

	if (unlikely(data->curr_sense < 0))
		return data->curr_sense;

	return snprintf(buf, PAGE_SIZE, "%d\n",
			ADC_TO_CURR(data->curr_sense, data->curr_gain));
}