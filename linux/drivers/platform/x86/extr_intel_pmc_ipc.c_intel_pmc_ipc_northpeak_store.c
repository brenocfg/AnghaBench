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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PMC_IPC_NORTHPEAK_CTRL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int intel_pmc_ipc_simple_command (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t intel_pmc_ipc_northpeak_store(struct device *dev,
					     struct device_attribute *attr,
					     const char *buf, size_t count)
{
	unsigned long val;
	int subcmd;
	int ret;

	if (kstrtoul(buf, 0, &val))
		return -EINVAL;

	if (val)
		subcmd = 1;
	else
		subcmd = 0;
	ret = intel_pmc_ipc_simple_command(PMC_IPC_NORTHPEAK_CTRL, subcmd);
	if (ret) {
		dev_err(dev, "command north %d error with %d\n", subcmd, ret);
		return ret;
	}
	return (ssize_t)count;
}