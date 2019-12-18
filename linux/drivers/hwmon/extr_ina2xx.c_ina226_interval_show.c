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
struct ina2xx_data {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  INA2XX_CONFIG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ina2xx_data* dev_get_drvdata (struct device*) ; 
 int ina226_reg_to_interval (unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t ina226_interval_show(struct device *dev,
				    struct device_attribute *da, char *buf)
{
	struct ina2xx_data *data = dev_get_drvdata(dev);
	int status;
	unsigned int regval;

	status = regmap_read(data->regmap, INA2XX_CONFIG, &regval);
	if (status)
		return status;

	return snprintf(buf, PAGE_SIZE, "%d\n", ina226_reg_to_interval(regval));
}