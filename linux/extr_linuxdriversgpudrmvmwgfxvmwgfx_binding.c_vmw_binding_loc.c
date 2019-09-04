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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct vmw_ctx_binding_state {int dummy; } ;
struct vmw_ctx_bindinfo {int dummy; } ;
struct vmw_binding_info {size_t* offsets; size_t size; } ;
typedef  enum vmw_ctx_binding_type { ____Placeholder_vmw_ctx_binding_type } vmw_ctx_binding_type ;

/* Variables and functions */
 struct vmw_binding_info* vmw_binding_infos ; 

__attribute__((used)) static struct vmw_ctx_bindinfo *
vmw_binding_loc(struct vmw_ctx_binding_state *cbs,
		enum vmw_ctx_binding_type bt, u32 shader_slot, u32 slot)
{
	const struct vmw_binding_info *b = &vmw_binding_infos[bt];
	size_t offset = b->offsets[shader_slot] + b->size*slot;

	return (struct vmw_ctx_bindinfo *)((u8 *) cbs + offset);
}