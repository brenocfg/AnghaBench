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
struct nd_btt {int /*<<< orphan*/  uuid; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,size_t,char const*,char*) ; 
 int /*<<< orphan*/  nd_device_lock (struct device*) ; 
 int /*<<< orphan*/  nd_device_unlock (struct device*) ; 
 size_t nd_uuid_store (struct device*,int /*<<< orphan*/ *,char const*,size_t) ; 
 struct nd_btt* to_nd_btt (struct device*) ; 

__attribute__((used)) static ssize_t uuid_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t len)
{
	struct nd_btt *nd_btt = to_nd_btt(dev);
	ssize_t rc;

	nd_device_lock(dev);
	rc = nd_uuid_store(dev, &nd_btt->uuid, buf, len);
	dev_dbg(dev, "result: %zd wrote: %s%s", rc, buf,
			buf[len - 1] == '\n' ? "" : "\n");
	nd_device_unlock(dev);

	return rc ? rc : len;
}