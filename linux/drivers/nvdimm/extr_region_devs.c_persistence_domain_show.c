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
struct nd_region {int /*<<< orphan*/  flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ND_REGION_PERSIST_CACHE ; 
 int /*<<< orphan*/  ND_REGION_PERSIST_MEMCTRL ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nd_region* to_nd_region (struct device*) ; 

__attribute__((used)) static ssize_t persistence_domain_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nd_region *nd_region = to_nd_region(dev);

	if (test_bit(ND_REGION_PERSIST_CACHE, &nd_region->flags))
		return sprintf(buf, "cpu_cache\n");
	else if (test_bit(ND_REGION_PERSIST_MEMCTRL, &nd_region->flags))
		return sprintf(buf, "memory_controller\n");
	else
		return sprintf(buf, "\n");
}