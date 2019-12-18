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
struct nsim_bus_dev {unsigned int num_vfs; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EBUSY ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  nsim_bus_dev_vfs_disable (struct nsim_bus_dev*) ; 
 int nsim_bus_dev_vfs_enable (struct nsim_bus_dev*,unsigned int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct nsim_bus_dev* to_nsim_bus_dev (struct device*) ; 

__attribute__((used)) static ssize_t
nsim_bus_dev_numvfs_store(struct device *dev, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);
	unsigned int num_vfs;
	int ret;

	ret = kstrtouint(buf, 0, &num_vfs);
	if (ret)
		return ret;

	rtnl_lock();
	if (nsim_bus_dev->num_vfs == num_vfs)
		goto exit_good;
	if (nsim_bus_dev->num_vfs && num_vfs) {
		ret = -EBUSY;
		goto exit_unlock;
	}

	if (num_vfs) {
		ret = nsim_bus_dev_vfs_enable(nsim_bus_dev, num_vfs);
		if (ret)
			goto exit_unlock;
	} else {
		nsim_bus_dev_vfs_disable(nsim_bus_dev);
	}
exit_good:
	ret = count;
exit_unlock:
	rtnl_unlock();

	return ret;
}