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
struct ttm_mem_type_manager {int /*<<< orphan*/  io_reserve_fastpath; } ;
struct TYPE_4__ {scalar_t__ io_reserved_count; } ;
struct ttm_mem_reg {size_t mem_type; TYPE_2__ bus; } ;
struct ttm_bo_device {TYPE_1__* driver; struct ttm_mem_type_manager* man; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* io_mem_free ) (struct ttm_bo_device*,struct ttm_mem_reg*) ;scalar_t__ io_mem_reserve; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ttm_bo_device*,struct ttm_mem_reg*) ; 

void ttm_mem_io_free(struct ttm_bo_device *bdev,
		     struct ttm_mem_reg *mem)
{
	struct ttm_mem_type_manager *man = &bdev->man[mem->mem_type];

	if (likely(man->io_reserve_fastpath))
		return;

	if (bdev->driver->io_mem_reserve &&
	    --mem->bus.io_reserved_count == 0 &&
	    bdev->driver->io_mem_free)
		bdev->driver->io_mem_free(bdev, mem);

}