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
struct rv3028_data {int /*<<< orphan*/  regmap; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  RV3028_TS_COUNT ; 
 struct rv3028_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t timestamp0_count_show(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct rv3028_data *rv3028 = dev_get_drvdata(dev->parent);
	int ret, count;

	ret = regmap_read(rv3028->regmap, RV3028_TS_COUNT, &count);
	if (ret)
		return ret;

	return sprintf(buf, "%u\n", count);
}