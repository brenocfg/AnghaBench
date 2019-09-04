#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fpga_region {int /*<<< orphan*/  bridge_list; int /*<<< orphan*/  info; struct dfl_fme_region_pdata* priv; } ;
struct dfl_fme_region_pdata {TYPE_1__* br; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int fpga_bridge_get_to_list (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fme_region_get_bridges(struct fpga_region *region)
{
	struct dfl_fme_region_pdata *pdata = region->priv;
	struct device *dev = &pdata->br->dev;

	return fpga_bridge_get_to_list(dev, region->info, &region->bridge_list);
}