#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  size; } ;
struct fimc_is {TYPE_2__ memory; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fimc_is_free_cpu_memory(struct fimc_is *is)
{
	struct device *dev = &is->pdev->dev;

	if (is->memory.vaddr == NULL)
		return;

	dma_free_coherent(dev, is->memory.size, is->memory.vaddr,
			  is->memory.paddr);
}