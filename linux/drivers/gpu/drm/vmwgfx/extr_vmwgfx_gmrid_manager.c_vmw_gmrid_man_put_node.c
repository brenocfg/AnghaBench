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
struct vmwgfx_gmrid_man {int /*<<< orphan*/  lock; int /*<<< orphan*/  used_gmr_pages; int /*<<< orphan*/  gmr_ida; } ;
struct ttm_mem_type_manager {scalar_t__ priv; } ;
struct ttm_mem_reg {int /*<<< orphan*/ * mm_node; scalar_t__ num_pages; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_gmrid_man_put_node(struct ttm_mem_type_manager *man,
				   struct ttm_mem_reg *mem)
{
	struct vmwgfx_gmrid_man *gman =
		(struct vmwgfx_gmrid_man *)man->priv;

	if (mem->mm_node) {
		ida_free(&gman->gmr_ida, mem->start);
		spin_lock(&gman->lock);
		gman->used_gmr_pages -= mem->num_pages;
		spin_unlock(&gman->lock);
		mem->mm_node = NULL;
	}
}