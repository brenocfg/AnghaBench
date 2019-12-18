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
struct tb_switch {int /*<<< orphan*/  dev; TYPE_1__* tb; int /*<<< orphan*/  dma_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int dma_port_flash_read (int /*<<< orphan*/ ,unsigned int,void*,size_t) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int restart_syscall () ; 

__attribute__((used)) static int tb_switch_nvm_read(void *priv, unsigned int offset, void *val,
			      size_t bytes)
{
	struct tb_switch *sw = priv;
	int ret;

	pm_runtime_get_sync(&sw->dev);

	if (!mutex_trylock(&sw->tb->lock)) {
		ret = restart_syscall();
		goto out;
	}

	ret = dma_port_flash_read(sw->dma_port, offset, val, bytes);
	mutex_unlock(&sw->tb->lock);

out:
	pm_runtime_mark_last_busy(&sw->dev);
	pm_runtime_put_autosuspend(&sw->dev);

	return ret;
}