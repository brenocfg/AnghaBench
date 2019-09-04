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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  GPIO_DIRECTION ; 
 int /*<<< orphan*/  GPIO_OUTPUT ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int,int /*<<< orphan*/ ) ; 
 struct ddb* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t fan_store(struct device *device, struct device_attribute *d,
			 const char *buf, size_t count)
{
	struct ddb *dev = dev_get_drvdata(device);
	u32 val;

	if (sscanf(buf, "%u\n", &val) != 1)
		return -EINVAL;
	ddbwritel(dev, 1, GPIO_DIRECTION);
	ddbwritel(dev, val & 1, GPIO_OUTPUT);
	return count;
}