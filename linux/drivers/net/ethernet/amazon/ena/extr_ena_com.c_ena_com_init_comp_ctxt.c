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
typedef  scalar_t__ u16 ;
struct ena_comp_ctx {int /*<<< orphan*/  wait_event; } ;
struct ena_com_admin_queue {int q_depth; int /*<<< orphan*/  comp_ctx; int /*<<< orphan*/  q_dmadev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 struct ena_comp_ctx* get_comp_ctxt (struct ena_com_admin_queue*,scalar_t__,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_com_init_comp_ctxt(struct ena_com_admin_queue *queue)
{
	size_t size = queue->q_depth * sizeof(struct ena_comp_ctx);
	struct ena_comp_ctx *comp_ctx;
	u16 i;

	queue->comp_ctx = devm_kzalloc(queue->q_dmadev, size, GFP_KERNEL);
	if (unlikely(!queue->comp_ctx)) {
		pr_err("memory allocation failed\n");
		return -ENOMEM;
	}

	for (i = 0; i < queue->q_depth; i++) {
		comp_ctx = get_comp_ctxt(queue, i, false);
		if (comp_ctx)
			init_completion(&comp_ctx->wait_event);
	}

	return 0;
}