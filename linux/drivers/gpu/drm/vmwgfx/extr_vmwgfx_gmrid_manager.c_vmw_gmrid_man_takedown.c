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
struct vmwgfx_gmrid_man {int /*<<< orphan*/  gmr_ida; } ;
struct ttm_mem_type_manager {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vmwgfx_gmrid_man*) ; 

__attribute__((used)) static int vmw_gmrid_man_takedown(struct ttm_mem_type_manager *man)
{
	struct vmwgfx_gmrid_man *gman =
		(struct vmwgfx_gmrid_man *)man->priv;

	if (gman) {
		ida_destroy(&gman->gmr_ida);
		kfree(gman);
	}
	return 0;
}