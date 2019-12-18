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
struct nd_region {int /*<<< orphan*/  dev; } ;
struct nd_pfn {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nd_device_register (struct device*) ; 
 int /*<<< orphan*/  is_memory (int /*<<< orphan*/ *) ; 
 struct nd_pfn* nd_pfn_alloc (struct nd_region*) ; 
 struct device* nd_pfn_devinit (struct nd_pfn*,int /*<<< orphan*/ *) ; 

struct device *nd_pfn_create(struct nd_region *nd_region)
{
	struct nd_pfn *nd_pfn;
	struct device *dev;

	if (!is_memory(&nd_region->dev))
		return NULL;

	nd_pfn = nd_pfn_alloc(nd_region);
	dev = nd_pfn_devinit(nd_pfn, NULL);

	__nd_device_register(dev);
	return dev;
}