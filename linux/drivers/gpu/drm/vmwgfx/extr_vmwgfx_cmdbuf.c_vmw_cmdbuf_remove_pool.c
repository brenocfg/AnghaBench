#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vmw_cmdbuf_man {int has_pool; int /*<<< orphan*/  handle; int /*<<< orphan*/  map; int /*<<< orphan*/  size; TYPE_3__* dev_priv; int /*<<< orphan*/ * cmd_space; int /*<<< orphan*/  map_obj; scalar_t__ using_mob; int /*<<< orphan*/  default_size; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  VMW_CMDBUF_INLINE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cmdbuf_idle (struct vmw_cmdbuf_man*,int,int) ; 

void vmw_cmdbuf_remove_pool(struct vmw_cmdbuf_man *man)
{
	if (!man->has_pool)
		return;

	man->has_pool = false;
	man->default_size = VMW_CMDBUF_INLINE_SIZE;
	(void) vmw_cmdbuf_idle(man, false, 10*HZ);
	if (man->using_mob) {
		(void) ttm_bo_kunmap(&man->map_obj);
		ttm_bo_put(man->cmd_space);
		man->cmd_space = NULL;
	} else {
		dma_free_coherent(&man->dev_priv->dev->pdev->dev,
				  man->size, man->map, man->handle);
	}
}