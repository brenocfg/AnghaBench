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
struct dev_dax {scalar_t__ id; struct dax_device* dax_dev; struct dax_region* region; } ;
struct dax_region {int /*<<< orphan*/  ida; } ;
struct dax_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dax_region_put (struct dax_region*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dev_dax*) ; 
 int /*<<< orphan*/  put_dax (struct dax_device*) ; 
 struct dev_dax* to_dev_dax (struct device*) ; 

__attribute__((used)) static void dev_dax_release(struct device *dev)
{
	struct dev_dax *dev_dax = to_dev_dax(dev);
	struct dax_region *dax_region = dev_dax->region;
	struct dax_device *dax_dev = dev_dax->dax_dev;

	if (dev_dax->id >= 0)
		ida_simple_remove(&dax_region->ida, dev_dax->id);
	dax_region_put(dax_region);
	put_dax(dax_dev);
	kfree(dev_dax);
}