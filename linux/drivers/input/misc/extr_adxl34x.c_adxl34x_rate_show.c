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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_rate; } ;
struct adxl34x {TYPE_1__ pdata; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int RATE (int /*<<< orphan*/ ) ; 
 struct adxl34x* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t adxl34x_rate_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct adxl34x *ac = dev_get_drvdata(dev);

	return sprintf(buf, "%u\n", RATE(ac->pdata.data_rate));
}