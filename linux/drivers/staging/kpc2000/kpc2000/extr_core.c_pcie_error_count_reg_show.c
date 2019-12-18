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
struct kp2000_device {scalar_t__ sysinfo_regs_base; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ REG_PCIE_ERROR_COUNT ; 
 struct kp2000_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pcie_error_count_reg_show(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
	struct kp2000_device *pcard = dev_get_drvdata(dev);
	u64 val;

	val = readq(pcard->sysinfo_regs_base + REG_PCIE_ERROR_COUNT);
	return sprintf(buf, "%016llx\n", val);
}