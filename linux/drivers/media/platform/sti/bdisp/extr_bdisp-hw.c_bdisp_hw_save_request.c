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
struct bdisp_request {int /*<<< orphan*/  nb_req; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct bdisp_node {int dummy; } ;
struct bdisp_ctx {TYPE_2__* bdisp_dev; int /*<<< orphan*/  vflip; int /*<<< orphan*/  hflip; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; struct bdisp_node** node; } ;
struct TYPE_3__ {struct bdisp_request copy_request; struct bdisp_node** copy_node; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ dbg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_NB_NODE ; 
 struct bdisp_node* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdisp_hw_save_request(struct bdisp_ctx *ctx)
{
	struct bdisp_node **copy_node = ctx->bdisp_dev->dbg.copy_node;
	struct bdisp_request *request = &ctx->bdisp_dev->dbg.copy_request;
	struct bdisp_node **node = ctx->node;
	int i;

	/* Request copy */
	request->src = ctx->src;
	request->dst = ctx->dst;
	request->hflip = ctx->hflip;
	request->vflip = ctx->vflip;
	request->nb_req++;

	/* Nodes copy */
	for (i = 0; i < MAX_NB_NODE; i++) {
		/* Allocate memory if not done yet */
		if (!copy_node[i]) {
			copy_node[i] = devm_kzalloc(ctx->bdisp_dev->dev,
						    sizeof(*copy_node[i]),
						    GFP_ATOMIC);
			if (!copy_node[i])
				return;
		}
		*copy_node[i] = *node[i];
	}
}