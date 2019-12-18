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
typedef  size_t u16 ;
struct efa_comp_ctx {int /*<<< orphan*/  wait_event; } ;
struct efa_com_admin_queue {int depth; size_t* comp_ctx; size_t* comp_ctx_pool; scalar_t__ comp_ctx_pool_next; int /*<<< orphan*/  comp_ctx_lock; int /*<<< orphan*/  dmadev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,size_t*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 struct efa_comp_ctx* efa_com_get_comp_ctx (struct efa_com_admin_queue*,size_t,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int efa_com_init_comp_ctxt(struct efa_com_admin_queue *aq)
{
	size_t pool_size = aq->depth * sizeof(*aq->comp_ctx_pool);
	size_t size = aq->depth * sizeof(struct efa_comp_ctx);
	struct efa_comp_ctx *comp_ctx;
	u16 i;

	aq->comp_ctx = devm_kzalloc(aq->dmadev, size, GFP_KERNEL);
	aq->comp_ctx_pool = devm_kzalloc(aq->dmadev, pool_size, GFP_KERNEL);
	if (!aq->comp_ctx || !aq->comp_ctx_pool) {
		devm_kfree(aq->dmadev, aq->comp_ctx_pool);
		devm_kfree(aq->dmadev, aq->comp_ctx);
		return -ENOMEM;
	}

	for (i = 0; i < aq->depth; i++) {
		comp_ctx = efa_com_get_comp_ctx(aq, i, false);
		if (comp_ctx)
			init_completion(&comp_ctx->wait_event);

		aq->comp_ctx_pool[i] = i;
	}

	spin_lock_init(&aq->comp_ctx_lock);

	aq->comp_ctx_pool_next = 0;

	return 0;
}