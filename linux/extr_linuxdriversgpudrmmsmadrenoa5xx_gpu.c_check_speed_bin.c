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
typedef  int u32 ;
struct nvmem_cell {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nvmem_cell*) ; 
 int /*<<< orphan*/  dev_pm_opp_set_supported_hw (struct device*,int*,int) ; 
 struct nvmem_cell* nvmem_cell_get (struct device*,char*) ; 
 int /*<<< orphan*/  nvmem_cell_put (struct nvmem_cell*) ; 
 scalar_t__ nvmem_cell_read (struct nvmem_cell*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_speed_bin(struct device *dev)
{
	struct nvmem_cell *cell;
	u32 bin, val;

	cell = nvmem_cell_get(dev, "speed_bin");

	/* If a nvmem cell isn't defined, nothing to do */
	if (IS_ERR(cell))
		return;

	bin = *((u32 *) nvmem_cell_read(cell, NULL));
	nvmem_cell_put(cell);

	val = (1 << bin);

	dev_pm_opp_set_supported_hw(dev, &val, 1);
}