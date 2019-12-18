#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mem_type; int /*<<< orphan*/  start; } ;
struct ttm_buffer_object {TYPE_1__ mem; scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__ offset; int /*<<< orphan*/  gmrId; } ;
typedef  TYPE_2__ SVGAGuestPtr ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_GMR_FRAMEBUFFER ; 
 scalar_t__ TTM_PL_VRAM ; 

void vmw_bo_get_guest_ptr(const struct ttm_buffer_object *bo,
			  SVGAGuestPtr *ptr)
{
	if (bo->mem.mem_type == TTM_PL_VRAM) {
		ptr->gmrId = SVGA_GMR_FRAMEBUFFER;
		ptr->offset = bo->offset;
	} else {
		ptr->gmrId = bo->mem.start;
		ptr->offset = 0;
	}
}