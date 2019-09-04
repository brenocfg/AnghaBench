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
struct vmw_cmdbuf_man {size_t cur_pos; struct vmw_cmdbuf_header* cur; } ;
struct vmw_cmdbuf_header {size_t reserved; TYPE_1__* cb_header; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_CB_FLAG_DX_CONTEXT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __vmw_cmdbuf_cur_flush (struct vmw_cmdbuf_man*) ; 
 int /*<<< orphan*/  vmw_cmdbuf_commit_cur (struct vmw_cmdbuf_man*,size_t,int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_cur_lock (struct vmw_cmdbuf_man*,int) ; 
 int /*<<< orphan*/  vmw_cmdbuf_cur_unlock (struct vmw_cmdbuf_man*) ; 

void vmw_cmdbuf_commit(struct vmw_cmdbuf_man *man, size_t size,
		       struct vmw_cmdbuf_header *header, bool flush)
{
	if (!header) {
		vmw_cmdbuf_commit_cur(man, size, flush);
		return;
	}

	(void) vmw_cmdbuf_cur_lock(man, false);
	__vmw_cmdbuf_cur_flush(man);
	WARN_ON(size > header->reserved);
	man->cur = header;
	man->cur_pos = size;
	if (!size)
		header->cb_header->flags &= ~SVGA_CB_FLAG_DX_CONTEXT;
	if (flush)
		__vmw_cmdbuf_cur_flush(man);
	vmw_cmdbuf_cur_unlock(man);
}