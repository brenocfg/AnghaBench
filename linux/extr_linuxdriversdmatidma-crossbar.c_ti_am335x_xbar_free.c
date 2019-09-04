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
struct ti_am335x_xbar_map {int /*<<< orphan*/  dma_line; int /*<<< orphan*/  mux_val; } ;
struct ti_am335x_xbar_data {int /*<<< orphan*/  iomem; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_am335x_xbar_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ti_am335x_xbar_map*) ; 
 int /*<<< orphan*/  ti_am335x_xbar_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_am335x_xbar_free(struct device *dev, void *route_data)
{
	struct ti_am335x_xbar_data *xbar = dev_get_drvdata(dev);
	struct ti_am335x_xbar_map *map = route_data;

	dev_dbg(dev, "Unmapping XBAR event %u on channel %u\n",
		map->mux_val, map->dma_line);

	ti_am335x_xbar_write(xbar->iomem, map->dma_line, 0);
	kfree(map);
}