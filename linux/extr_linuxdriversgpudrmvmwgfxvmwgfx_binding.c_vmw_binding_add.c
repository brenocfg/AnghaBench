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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_ctx_binding_state {int /*<<< orphan*/  list; } ;
struct vmw_ctx_bindinfo {size_t bt; int scrubbed; int /*<<< orphan*/  res_list; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/ * ctx; } ;
struct vmw_binding_info {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct vmw_ctx_bindinfo*,struct vmw_ctx_bindinfo const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_binding_drop (struct vmw_ctx_bindinfo*) ; 
 struct vmw_binding_info* vmw_binding_infos ; 
 struct vmw_ctx_bindinfo* vmw_binding_loc (struct vmw_ctx_binding_state*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vmw_binding_add(struct vmw_ctx_binding_state *cbs,
		    const struct vmw_ctx_bindinfo *bi,
		    u32 shader_slot, u32 slot)
{
	struct vmw_ctx_bindinfo *loc =
		vmw_binding_loc(cbs, bi->bt, shader_slot, slot);
	const struct vmw_binding_info *b = &vmw_binding_infos[bi->bt];

	if (loc->ctx != NULL)
		vmw_binding_drop(loc);

	memcpy(loc, bi, b->size);
	loc->scrubbed = false;
	list_add(&loc->ctx_list, &cbs->list);
	INIT_LIST_HEAD(&loc->res_list);
}