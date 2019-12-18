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
struct vmw_cmdbuf_man {int /*<<< orphan*/  error_mutex; int /*<<< orphan*/  space_mutex; int /*<<< orphan*/  cur_mutex; int /*<<< orphan*/  headers; int /*<<< orphan*/  dheaders; int /*<<< orphan*/  work; TYPE_1__* dev_priv; int /*<<< orphan*/  has_pool; } ;
struct TYPE_2__ {int /*<<< orphan*/  error_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int HZ ; 
 int /*<<< orphan*/  SVGA_IRQFLAG_ERROR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vmw_cmdbuf_man*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_cmdbuf_idle (struct vmw_cmdbuf_man*,int,int) ; 
 scalar_t__ vmw_cmdbuf_startstop (struct vmw_cmdbuf_man*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmw_generic_waiter_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vmw_cmdbuf_man_destroy(struct vmw_cmdbuf_man *man)
{
	WARN_ON_ONCE(man->has_pool);
	(void) vmw_cmdbuf_idle(man, false, 10*HZ);

	if (vmw_cmdbuf_startstop(man, 0, false))
		DRM_ERROR("Failed stopping command buffer contexts.\n");

	vmw_generic_waiter_remove(man->dev_priv, SVGA_IRQFLAG_ERROR,
				  &man->dev_priv->error_waiters);
	(void) cancel_work_sync(&man->work);
	dma_pool_destroy(man->dheaders);
	dma_pool_destroy(man->headers);
	mutex_destroy(&man->cur_mutex);
	mutex_destroy(&man->space_mutex);
	mutex_destroy(&man->error_mutex);
	kfree(man);
}