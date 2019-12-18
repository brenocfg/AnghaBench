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
struct rio_mport {int sys_size; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct rio_mport* to_rio_mport (struct device*) ; 

__attribute__((used)) static ssize_t sys_size_show(struct device *dev, struct device_attribute *attr,
			   char *buf)
{
	struct rio_mport *mport = to_rio_mport(dev);

	if (mport)
		return sprintf(buf, "%u\n", mport->sys_size);
	else
		return -ENODEV;
}