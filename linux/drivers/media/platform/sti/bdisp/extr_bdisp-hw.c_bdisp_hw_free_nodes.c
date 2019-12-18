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
struct bdisp_node {int dummy; } ;
struct bdisp_ctx {int /*<<< orphan*/ * node_paddr; scalar_t__* node; TYPE_1__* bdisp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_WRITE_COMBINE ; 
 int MAX_NB_NODE ; 
 int /*<<< orphan*/  dma_free_attrs (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bdisp_hw_free_nodes(struct bdisp_ctx *ctx)
{
	if (ctx && ctx->node[0])
		dma_free_attrs(ctx->bdisp_dev->dev,
			       sizeof(struct bdisp_node) * MAX_NB_NODE,
			       ctx->node[0], ctx->node_paddr[0],
			       DMA_ATTR_WRITE_COMBINE);
}