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
struct vmw_ctx_binding_state {int /*<<< orphan*/  list; } ;
struct vmw_ctx_bindinfo {size_t bt; TYPE_1__* res; int /*<<< orphan*/  res_list; int /*<<< orphan*/  ctx_list; int /*<<< orphan*/  scrubbed; int /*<<< orphan*/ * ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  binding_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct vmw_ctx_bindinfo*,struct vmw_ctx_bindinfo const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_binding_drop (struct vmw_ctx_bindinfo*) ; 
 TYPE_2__* vmw_binding_infos ; 

__attribute__((used)) static void vmw_binding_transfer(struct vmw_ctx_binding_state *cbs,
				 const struct vmw_ctx_binding_state *from,
				 const struct vmw_ctx_bindinfo *bi)
{
	size_t offset = (unsigned long)bi - (unsigned long)from;
	struct vmw_ctx_bindinfo *loc = (struct vmw_ctx_bindinfo *)
		((unsigned long) cbs + offset);

	if (loc->ctx != NULL) {
		WARN_ON(bi->scrubbed);

		vmw_binding_drop(loc);
	}

	if (bi->res != NULL) {
		memcpy(loc, bi, vmw_binding_infos[bi->bt].size);
		list_add_tail(&loc->ctx_list, &cbs->list);
		list_add_tail(&loc->res_list, &loc->res->binding_head);
	}
}