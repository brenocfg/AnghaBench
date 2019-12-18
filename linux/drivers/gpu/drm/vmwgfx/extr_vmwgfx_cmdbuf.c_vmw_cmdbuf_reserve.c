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
struct vmw_cmdbuf_man {int dummy; } ;
struct vmw_cmdbuf_header {size_t size; size_t reserved; void* cmd; TYPE_1__* cb_header; } ;
struct TYPE_2__ {int dxContext; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int SVGA3D_INVALID_ID ; 
 int /*<<< orphan*/  SVGA_CB_FLAG_DX_CONTEXT ; 
 void* vmw_cmdbuf_reserve_cur (struct vmw_cmdbuf_man*,size_t,int,int) ; 

void *vmw_cmdbuf_reserve(struct vmw_cmdbuf_man *man, size_t size,
			 int ctx_id, bool interruptible,
			 struct vmw_cmdbuf_header *header)
{
	if (!header)
		return vmw_cmdbuf_reserve_cur(man, size, ctx_id, interruptible);

	if (size > header->size)
		return ERR_PTR(-EINVAL);

	if (ctx_id != SVGA3D_INVALID_ID) {
		header->cb_header->flags |= SVGA_CB_FLAG_DX_CONTEXT;
		header->cb_header->dxContext = ctx_id;
	}

	header->reserved = size;
	return header->cmd;
}