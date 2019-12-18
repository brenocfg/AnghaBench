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
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_sw_context {int /*<<< orphan*/  bo_relocations; int /*<<< orphan*/  ctx; TYPE_1__* fp; } ;
struct vmw_relocation {int /*<<< orphan*/  head; struct vmw_buffer_object* vbo; int /*<<< orphan*/ * mob_loc; } ;
struct vmw_private {int dummy; } ;
struct vmw_buffer_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfile; } ;
typedef  int /*<<< orphan*/  SVGAMobId ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct vmw_buffer_object*) ; 
 int PTR_ERR (struct vmw_buffer_object*) ; 
 int /*<<< orphan*/  VMW_DEBUG_USER (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 struct vmw_buffer_object* vmw_user_bo_noref_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_user_bo_noref_release () ; 
 int vmw_validation_add_bo (int /*<<< orphan*/ ,struct vmw_buffer_object*,int,int) ; 
 struct vmw_relocation* vmw_validation_mem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_validation_preload_bo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmw_translate_mob_ptr(struct vmw_private *dev_priv,
				 struct vmw_sw_context *sw_context,
				 SVGAMobId *id,
				 struct vmw_buffer_object **vmw_bo_p)
{
	struct vmw_buffer_object *vmw_bo;
	uint32_t handle = *id;
	struct vmw_relocation *reloc;
	int ret;

	vmw_validation_preload_bo(sw_context->ctx);
	vmw_bo = vmw_user_bo_noref_lookup(sw_context->fp->tfile, handle);
	if (IS_ERR(vmw_bo)) {
		VMW_DEBUG_USER("Could not find or use MOB buffer.\n");
		return PTR_ERR(vmw_bo);
	}

	ret = vmw_validation_add_bo(sw_context->ctx, vmw_bo, true, false);
	vmw_user_bo_noref_release();
	if (unlikely(ret != 0))
		return ret;

	reloc = vmw_validation_mem_alloc(sw_context->ctx, sizeof(*reloc));
	if (!reloc)
		return -ENOMEM;

	reloc->mob_loc = id;
	reloc->vbo = vmw_bo;

	*vmw_bo_p = vmw_bo;
	list_add_tail(&reloc->head, &sw_context->bo_relocations);

	return 0;
}