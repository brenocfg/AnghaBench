#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct vmw_sw_context {size_t cur_reloc; TYPE_1__* val_bufs; struct vmw_relocation* relocs; } ;
struct vmw_relocation {size_t index; int /*<<< orphan*/ * mob_loc; TYPE_2__* location; } ;
struct ttm_validate_buffer {struct ttm_buffer_object* bo; } ;
struct TYPE_6__ {int mem_type; int /*<<< orphan*/  start; } ;
struct ttm_buffer_object {TYPE_3__ mem; int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  gmrId; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {struct ttm_validate_buffer base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  SVGA_GMR_FRAMEBUFFER ; 
#define  TTM_PL_VRAM 130 
#define  VMW_PL_GMR 129 
#define  VMW_PL_MOB 128 
 int /*<<< orphan*/  vmw_free_relocations (struct vmw_sw_context*) ; 

__attribute__((used)) static void vmw_apply_relocations(struct vmw_sw_context *sw_context)
{
	uint32_t i;
	struct vmw_relocation *reloc;
	struct ttm_validate_buffer *validate;
	struct ttm_buffer_object *bo;

	for (i = 0; i < sw_context->cur_reloc; ++i) {
		reloc = &sw_context->relocs[i];
		validate = &sw_context->val_bufs[reloc->index].base;
		bo = validate->bo;
		switch (bo->mem.mem_type) {
		case TTM_PL_VRAM:
			reloc->location->offset += bo->offset;
			reloc->location->gmrId = SVGA_GMR_FRAMEBUFFER;
			break;
		case VMW_PL_GMR:
			reloc->location->gmrId = bo->mem.start;
			break;
		case VMW_PL_MOB:
			*reloc->mob_loc = bo->mem.start;
			break;
		default:
			BUG();
		}
	}
	vmw_free_relocations(sw_context);
}