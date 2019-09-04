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
struct w83795_data {int enable_dts; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct w83795_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
show_dts_mode(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct w83795_data *data = dev_get_drvdata(dev);
	int tmp;

	if (data->enable_dts & 2)
		tmp = 5;
	else
		tmp = 6;

	return sprintf(buf, "%d\n", tmp);
}