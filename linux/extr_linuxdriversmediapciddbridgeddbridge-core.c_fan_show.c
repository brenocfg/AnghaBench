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
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ddb {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_OUTPUT ; 
 int ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t fan_show(struct device *device,
			struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	u32 val;

	val = ddbreadl(dev, GPIO_OUTPUT) & 1;
	return sprintf(buf, "%d\n", val);
}