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
struct tegra_bo {int /*<<< orphan*/  paddr; struct sg_table* sgt; } ;
struct sg_table {int dummy; } ;
struct host1x_bo {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct tegra_bo* host1x_to_tegra_bo (struct host1x_bo*) ; 

__attribute__((used)) static dma_addr_t tegra_bo_pin(struct host1x_bo *bo, struct sg_table **sgt)
{
	struct tegra_bo *obj = host1x_to_tegra_bo(bo);

	*sgt = obj->sgt;

	return obj->paddr;
}