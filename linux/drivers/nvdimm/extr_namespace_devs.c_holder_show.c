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
struct nd_namespace_common {scalar_t__ claim; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* dev_name (scalar_t__) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 struct nd_namespace_common* to_ndns (struct device*) ; 

__attribute__((used)) static ssize_t holder_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_namespace_common *ndns = to_ndns(dev);
	ssize_t rc;

	nd_device_lock(dev);
	rc = sprintf(buf, "%s\n", ndns->claim ? dev_name(ndns->claim) : "");
	nd_device_unlock(dev);

	return rc;
}