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
struct arm_spe_pmu {int /*<<< orphan*/  supported_cpus; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ *) ; 
 struct arm_spe_pmu* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static ssize_t arm_spe_pmu_get_attr_cpumask(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct arm_spe_pmu *spe_pmu = dev_get_drvdata(dev);

	return cpumap_print_to_pagebuf(true, buf, &spe_pmu->supported_cpus);
}