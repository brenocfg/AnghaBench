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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_sw_context {scalar_t__ cur_reloc; struct vmw_relocation* relocs; TYPE_1__* fp; } ;
struct vmw_relocation {int /*<<< orphan*/  index; TYPE_2__* location; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  gmrId; } ;
struct TYPE_4__ {int /*<<< orphan*/  tfile; } ;
typedef  TYPE_2__ SVGAGuestPtr ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 scalar_t__ VMWGFX_MAX_RELOCATIONS ; 
 scalar_t__ unlikely (int) ; 
 int vmw_bo_to_validate_list (struct vmw_sw_context*,struct vmw_buffer_object*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 int vmw_user_bo_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_buffer_object**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vmw_translate_guest_ptr(struct vmw_private *dev_priv,
				   struct vmw_sw_context *sw_context,
				   SVGAGuestPtr *ptr,
				   struct vmw_buffer_object **vmw_bo_p)
{
	struct vmw_buffer_object *vmw_bo = NULL;
	uint32_t handle = ptr->gmrId;
	struct vmw_relocation *reloc;
	int ret;

	ret = vmw_user_bo_lookup(sw_context->fp->tfile, handle, &vmw_bo, NULL);
	if (unlikely(ret != 0)) {
		DRM_ERROR("Could not find or use GMR region.\n");
		ret = -EINVAL;
		goto out_no_reloc;
	}

	if (unlikely(sw_context->cur_reloc >= VMWGFX_MAX_RELOCATIONS)) {
		DRM_ERROR("Max number relocations per submission"
			  " exceeded\n");
		ret = -EINVAL;
		goto out_no_reloc;
	}

	reloc = &sw_context->relocs[sw_context->cur_reloc++];
	reloc->location = ptr;

	ret = vmw_bo_to_validate_list(sw_context, vmw_bo, false, &reloc->index);
	if (unlikely(ret != 0))
		goto out_no_reloc;

	*vmw_bo_p = vmw_bo;
	return 0;

out_no_reloc:
	vmw_bo_unreference(&vmw_bo);
	*vmw_bo_p = NULL;
	return ret;
}