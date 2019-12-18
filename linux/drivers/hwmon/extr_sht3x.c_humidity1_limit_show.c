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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sht3x_data {int /*<<< orphan*/ * humidity_limits; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {size_t index; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct sht3x_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t humidity1_limit_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct sht3x_data *data = dev_get_drvdata(dev);
	u8 index = to_sensor_dev_attr(attr)->index;
	u32 humidity_limit = data->humidity_limits[index];

	return scnprintf(buf, PAGE_SIZE, "%u\n", humidity_limit);
}