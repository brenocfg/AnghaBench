#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {int* name; } ;
struct device_attribute {TYPE_2__ attr; } ;
struct device {int dummy; } ;
struct ddb {TYPE_1__* i2c; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {struct i2c_adapter adap; } ;

/* Variables and functions */
 struct ddb* dev_get_drvdata (struct device*) ; 
 scalar_t__ i2c_read_regs (struct i2c_adapter*,int,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t ctemp_show(struct device *device,
			  struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	struct i2c_adapter *adap;
	int temp;
	u8 tmp[2];
	int num = attr->attr.name[4] - 0x30;

	adap = &dev->i2c[num].adap;
	if (!adap)
		return 0;
	if (i2c_read_regs(adap, 0x49, 0, tmp, 2) < 0)
		if (i2c_read_regs(adap, 0x4d, 0, tmp, 2) < 0)
			return sprintf(buf, "no sensor\n");
	temp = tmp[0] * 1000;
	return sprintf(buf, "%d\n", temp);
}