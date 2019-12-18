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
struct delta_ipc_ctx {TYPE_1__* ipc_buf; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int paddr; void* vaddr; } ;

/* Variables and functions */

__attribute__((used)) static inline dma_addr_t to_paddr(struct delta_ipc_ctx *ctx, void *vaddr)
{
	return (ctx->ipc_buf->paddr + (vaddr - ctx->ipc_buf->vaddr));
}