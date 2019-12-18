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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {TYPE_1__* vsi; } ;
struct mtk_mdp_ctx {TYPE_2__ vpu; } ;
struct mtk_mdp_addr {scalar_t__* addr; } ;
struct mdp_buffer {scalar_t__* addr_mva; } ;
struct TYPE_3__ {struct mdp_buffer dst_buffer; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 

void mtk_mdp_hw_set_output_addr(struct mtk_mdp_ctx *ctx,
				struct mtk_mdp_addr *addr)
{
	struct mdp_buffer *dst_buf = &ctx->vpu.vsi->dst_buffer;
	int i;

	for (i = 0; i < ARRAY_SIZE(addr->addr); i++)
		dst_buf->addr_mva[i] = (uint64_t)addr->addr[i];
}