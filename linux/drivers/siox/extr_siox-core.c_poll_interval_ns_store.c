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
typedef  int /*<<< orphan*/  u64 ;
struct siox_master {int /*<<< orphan*/  poll_interval; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtou64 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siox_master_lock (struct siox_master*) ; 
 int /*<<< orphan*/  siox_master_unlock (struct siox_master*) ; 
 struct siox_master* to_siox_master (struct device*) ; 

__attribute__((used)) static ssize_t poll_interval_ns_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct siox_master *smaster = to_siox_master(dev);
	int ret;
	u64 val;

	ret = kstrtou64(buf, 0, &val);
	if (ret < 0)
		return ret;

	siox_master_lock(smaster);

	smaster->poll_interval = nsecs_to_jiffies(val);

	siox_master_unlock(smaster);

	return count;
}