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
struct s3c_hwmon_chcfg {int mult; int /*<<< orphan*/  div; } ;
struct s3c_hwmon {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct s3c_hwmon* dev_get_drvdata (struct device*) ; 
 struct s3c_hwmon_pdata* dev_get_platdata (struct device*) ; 
 int s3c_hwmon_read_ch (struct device*,struct s3c_hwmon*,size_t) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t s3c_hwmon_ch_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	struct sensor_device_attribute *sen_attr = to_sensor_dev_attr(attr);
	struct s3c_hwmon *hwmon = dev_get_drvdata(dev);
	struct s3c_hwmon_pdata *pdata = dev_get_platdata(dev);
	struct s3c_hwmon_chcfg *cfg;
	int ret;

	cfg = pdata->in[sen_attr->index];

	ret = s3c_hwmon_read_ch(dev, hwmon, sen_attr->index);
	if (ret < 0)
		return ret;

	ret *= cfg->mult;
	ret = DIV_ROUND_CLOSEST(ret, cfg->div);

	return snprintf(buf, PAGE_SIZE, "%d\n", ret);
}