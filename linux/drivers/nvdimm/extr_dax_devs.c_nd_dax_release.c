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
struct nd_region {int /*<<< orphan*/  dax_ida; } ;
struct nd_pfn {struct nd_dax* uuid; int /*<<< orphan*/  id; int /*<<< orphan*/  ndns; } ;
struct nd_dax {struct nd_pfn nd_pfn; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nd_dax*) ; 
 int /*<<< orphan*/  nd_detach_ndns (struct device*,int /*<<< orphan*/ *) ; 
 struct nd_dax* to_nd_dax (struct device*) ; 
 struct nd_region* to_nd_region (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nd_dax_release(struct device *dev)
{
	struct nd_region *nd_region = to_nd_region(dev->parent);
	struct nd_dax *nd_dax = to_nd_dax(dev);
	struct nd_pfn *nd_pfn = &nd_dax->nd_pfn;

	dev_dbg(dev, "trace\n");
	nd_detach_ndns(dev, &nd_pfn->ndns);
	ida_simple_remove(&nd_region->dax_ida, nd_pfn->id);
	kfree(nd_pfn->uuid);
	kfree(nd_dax);
}