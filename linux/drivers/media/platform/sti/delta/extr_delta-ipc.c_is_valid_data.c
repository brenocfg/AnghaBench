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
typedef  int u32 ;
struct delta_ipc_ctx {TYPE_1__* ipc_buf; } ;
struct TYPE_2__ {void* vaddr; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_valid_data(struct delta_ipc_ctx *ctx,
				 void *data, u32 size)
{
	return ((data >= ctx->ipc_buf->vaddr) &&
		((data + size) <= (ctx->ipc_buf->vaddr + ctx->ipc_buf->size)));
}