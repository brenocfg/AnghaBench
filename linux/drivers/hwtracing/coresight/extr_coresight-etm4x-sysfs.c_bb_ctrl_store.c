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
struct etmv4_config {unsigned long bb_ctrl; } ;
struct etmv4_drvdata {int trcbb; scalar_t__ nr_addr_cmp; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ BMVAL (unsigned long,int /*<<< orphan*/ ,int) ; 
 size_t EINVAL ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t bb_ctrl_store(struct device *dev,
			     struct device_attribute *attr,
			     const char *buf, size_t size)
{
	unsigned long val;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	if (kstrtoul(buf, 16, &val))
		return -EINVAL;
	if (drvdata->trcbb == false)
		return -EINVAL;
	if (!drvdata->nr_addr_cmp)
		return -EINVAL;
	/*
	 * Bit[7:0] selects which address range comparator is used for
	 * branch broadcast control.
	 */
	if (BMVAL(val, 0, 7) > drvdata->nr_addr_cmp)
		return -EINVAL;

	config->bb_ctrl = val;
	return size;
}