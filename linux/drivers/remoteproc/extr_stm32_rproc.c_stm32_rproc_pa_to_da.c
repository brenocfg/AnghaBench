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
typedef  scalar_t__ u64 ;
struct stm32_rproc_mem {scalar_t__ bus_addr; scalar_t__ size; scalar_t__ dev_addr; } ;
struct stm32_rproc {unsigned int nb_rmems; struct stm32_rproc_mem* rmems; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct rproc {TYPE_1__ dev; struct stm32_rproc* priv; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int stm32_rproc_pa_to_da(struct rproc *rproc, phys_addr_t pa, u64 *da)
{
	unsigned int i;
	struct stm32_rproc *ddata = rproc->priv;
	struct stm32_rproc_mem *p_mem;

	for (i = 0; i < ddata->nb_rmems; i++) {
		p_mem = &ddata->rmems[i];

		if (pa < p_mem->bus_addr ||
		    pa >= p_mem->bus_addr + p_mem->size)
			continue;
		*da = pa - p_mem->bus_addr + p_mem->dev_addr;
		dev_dbg(rproc->dev.parent, "pa %pa to da %llx\n", &pa, *da);
		return 0;
	}

	return -EINVAL;
}