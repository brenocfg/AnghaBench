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
struct vmw_cmdbuf_man {int /*<<< orphan*/  headers; int /*<<< orphan*/  alloc_queue; int /*<<< orphan*/  lock; } ;
struct vmw_cmdbuf_header {int /*<<< orphan*/  handle; scalar_t__ cb_header; int /*<<< orphan*/  node; scalar_t__ inline_space; struct vmw_cmdbuf_man* man; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mm_remove_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmw_cmdbuf_header*) ; 
 int /*<<< orphan*/  lockdep_assert_held_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cmdbuf_header_inline_free (struct vmw_cmdbuf_header*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vmw_cmdbuf_header_free(struct vmw_cmdbuf_header *header)
{
	struct vmw_cmdbuf_man *man = header->man;

	lockdep_assert_held_once(&man->lock);

	if (header->inline_space) {
		vmw_cmdbuf_header_inline_free(header);
		return;
	}

	drm_mm_remove_node(&header->node);
	wake_up_all(&man->alloc_queue);
	if (header->cb_header)
		dma_pool_free(man->headers, header->cb_header,
			      header->handle);
	kfree(header);
}