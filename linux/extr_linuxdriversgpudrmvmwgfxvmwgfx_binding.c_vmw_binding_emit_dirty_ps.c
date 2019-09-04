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
typedef  scalar_t__ u32 ;
struct vmw_dx_shader_bindings {int /*<<< orphan*/  dirty; } ;
struct vmw_ctx_binding_state {struct vmw_dx_shader_bindings* per_shader; } ;

/* Variables and functions */
 scalar_t__ SVGA3D_NUM_SHADERTYPE_DX10 ; 
 int /*<<< orphan*/  VMW_BINDING_PS_SR_BIT ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vmw_emit_set_sr (struct vmw_ctx_binding_state*,scalar_t__) ; 

__attribute__((used)) static int vmw_binding_emit_dirty_ps(struct vmw_ctx_binding_state *cbs)
{
	struct vmw_dx_shader_bindings *sb = &cbs->per_shader[0];
	u32 i;
	int ret;

	for (i = 0; i < SVGA3D_NUM_SHADERTYPE_DX10; ++i, ++sb) {
		if (!test_bit(VMW_BINDING_PS_SR_BIT, &sb->dirty))
			continue;

		ret = vmw_emit_set_sr(cbs, i);
		if (ret)
			break;

		__clear_bit(VMW_BINDING_PS_SR_BIT, &sb->dirty);
	}

	return 0;
}