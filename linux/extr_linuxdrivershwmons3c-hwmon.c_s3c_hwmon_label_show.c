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
struct sensor_device_attribute {size_t index; } ;
struct s3c_hwmon_pdata {struct s3c_hwmon_chcfg** in; } ;
struct s3c_hwmon_chcfg {char* name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct s3c_hwmon_pdata* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t s3c_hwmon_label_show(struct device *dev,
				    struct device_attribute *attr,
				    char *buf)
{
	struct sensor_device_attribute *sen_attr = to_sensor_dev_attr(attr);
	struct s3c_hwmon_pdata *pdata = dev_get_platdata(dev);
	struct s3c_hwmon_chcfg *cfg;

	cfg = pdata->in[sen_attr->index];

	return snprintf(buf, PAGE_SIZE, "%s\n", cfg->name);
}