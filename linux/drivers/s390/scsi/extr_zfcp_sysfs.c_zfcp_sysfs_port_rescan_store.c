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
struct zfcp_adapter {int /*<<< orphan*/  scan_work; int /*<<< orphan*/  work_queue; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ccw_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 
 struct zfcp_adapter* zfcp_ccw_adapter_by_cdev (struct ccw_device*) ; 
 int /*<<< orphan*/  zfcp_ccw_adapter_put (struct zfcp_adapter*) ; 

__attribute__((used)) static ssize_t zfcp_sysfs_port_rescan_store(struct device *dev,
					    struct device_attribute *attr,
					    const char *buf, size_t count)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct zfcp_adapter *adapter = zfcp_ccw_adapter_by_cdev(cdev);

	if (!adapter)
		return -ENODEV;

	/*
	 * Users wish is our command: immediately schedule and flush a
	 * worker to conduct a synchronous port scan, that is, neither
	 * a random delay nor a rate limit is applied here.
	 */
	queue_delayed_work(adapter->work_queue, &adapter->scan_work, 0);
	flush_delayed_work(&adapter->scan_work);
	zfcp_ccw_adapter_put(adapter);

	return (ssize_t) count;
}