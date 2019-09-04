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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct dev_dax {int num_resources; int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ resource_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 struct dev_dax* to_dev_dax (struct device*) ; 

__attribute__((used)) static ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct dev_dax *dev_dax = to_dev_dax(dev);
	unsigned long long size = 0;
	int i;

	for (i = 0; i < dev_dax->num_resources; i++)
		size += resource_size(&dev_dax->res[i]);

	return sprintf(buf, "%llu\n", size);
}