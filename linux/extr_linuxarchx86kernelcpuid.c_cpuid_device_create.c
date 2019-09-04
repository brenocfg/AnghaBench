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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUID_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  cpuid_class ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int) ; 

__attribute__((used)) static int cpuid_device_create(unsigned int cpu)
{
	struct device *dev;

	dev = device_create(cpuid_class, NULL, MKDEV(CPUID_MAJOR, cpu), NULL,
			    "cpu%d", cpu);
	return PTR_ERR_OR_ZERO(dev);
}