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
struct nd_btt {int /*<<< orphan*/  size; } ;
struct device_attribute {int dummy; } ;
struct device {scalar_t__ driver; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 

__attribute__((used)) static ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t rc;

	nd_device_lock(dev);
	if (dev->driver)
		rc = sprintf(buf, "%llu\n", nd_btt->size);
	else {
		/* no size to convey if the btt instance is disabled */
		rc = -ENXIO;
	}
	nd_device_unlock(dev);

	return rc;
}