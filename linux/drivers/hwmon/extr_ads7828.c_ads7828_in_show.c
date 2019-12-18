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
typedef  int /*<<< orphan*/  u8 ;
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ads7828_data {unsigned int lsb_resol; int /*<<< orphan*/  regmap; int /*<<< orphan*/  cmd_byte; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int /*<<< orphan*/  ads7828_cmd_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ads7828_data* dev_get_drvdata (struct device*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int sprintf (char*,char*,int) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t ads7828_in_show(struct device *dev,
			       struct device_attribute *da, char *buf)
{
	struct sensor_device_attribute *attr = to_sensor_dev_attr(da);
	struct ads7828_data *data = dev_get_drvdata(dev);
	u8 cmd = ads7828_cmd_byte(data->cmd_byte, attr->index);
	unsigned int regval;
	int err;

	err = regmap_read(data->regmap, cmd, &regval);
	if (err < 0)
		return err;

	return sprintf(buf, "%d\n",
		       DIV_ROUND_CLOSEST(regval * data->lsb_resol, 1000));
}