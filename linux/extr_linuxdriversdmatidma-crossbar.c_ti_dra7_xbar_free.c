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
struct ti_dra7_xbar_map {int /*<<< orphan*/  xbar_out; int /*<<< orphan*/  xbar_in; } ;
struct ti_dra7_xbar_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dma_inuse; int /*<<< orphan*/  safe_val; int /*<<< orphan*/  iomem; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_dra7_xbar_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ti_dra7_xbar_map*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_dra7_xbar_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_dra7_xbar_free(struct device *dev, void *route_data)
{
	struct ti_dra7_xbar_data *xbar = dev_get_drvdata(dev);
	struct ti_dra7_xbar_map *map = route_data;

	dev_dbg(dev, "Unmapping XBAR%u (was routed to %d)\n",
		map->xbar_in, map->xbar_out);

	ti_dra7_xbar_write(xbar->iomem, map->xbar_out, xbar->safe_val);
	mutex_lock(&xbar->mutex);
	clear_bit(map->xbar_out, xbar->dma_inuse);
	mutex_unlock(&xbar->mutex);
	kfree(map);
}