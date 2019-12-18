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
struct nd_region {struct device* dax_seed; struct device* pfn_seed; struct device* btt_seed; } ;
struct nd_namespace_common {int dummy; } ;
struct device {scalar_t__ driver; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ is_nd_btt (struct device*) ; 
 scalar_t__ is_nd_dax (struct device*) ; 
 scalar_t__ is_nd_pfn (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_idle(struct device *dev, struct nd_namespace_common *ndns)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct device *seed = NULL;

	if (is_nd_btt(dev))
		seed = nd_region->btt_seed;
	else if (is_nd_pfn(dev))
		seed = nd_region->pfn_seed;
	else if (is_nd_dax(dev))
		seed = nd_region->dax_seed;

	if (seed == dev || ndns || dev->driver)
		return false;
	return true;
}