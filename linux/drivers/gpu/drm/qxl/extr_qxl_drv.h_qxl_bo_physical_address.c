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
typedef  unsigned long uint64_t ;
struct qxl_memslot {int gpu_offset; unsigned long high_bits; } ;
struct qxl_device {struct qxl_memslot surfaces_slot; struct qxl_memslot main_slot; } ;
struct TYPE_3__ {scalar_t__ mem_type; } ;
struct TYPE_4__ {int offset; TYPE_1__ mem; } ;
struct qxl_bo {TYPE_2__ tbo; } ;

/* Variables and functions */
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline uint64_t
qxl_bo_physical_address(struct qxl_device *qdev, struct qxl_bo *bo,
			unsigned long offset)
{
	struct qxl_memslot *slot =
		(bo->tbo.mem.mem_type == TTM_PL_VRAM)
		? &qdev->main_slot : &qdev->surfaces_slot;

	WARN_ON_ONCE((bo->tbo.offset & slot->gpu_offset) != slot->gpu_offset);

	/* TODO - need to hold one of the locks to read tbo.offset */
	return slot->high_bits | (bo->tbo.offset - slot->gpu_offset + offset);
}