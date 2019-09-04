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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct atk_sensor_data {char* acpi_name; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct atk_sensor_data* label_to_atk_sensor (struct device_attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t atk_label_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct atk_sensor_data *s = label_to_atk_sensor(attr);

	return sprintf(buf, "%s\n", s->acpi_name);
}