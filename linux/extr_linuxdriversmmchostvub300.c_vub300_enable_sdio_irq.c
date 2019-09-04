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
struct vub300_mmc_host {int irq_enabled; int /*<<< orphan*/  kref; int /*<<< orphan*/  irq_mutex; scalar_t__ irq_disabled; int /*<<< orphan*/  mmc; scalar_t__ irqs_queued; int /*<<< orphan*/  interface; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vub300_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vub300_delete ; 
 int /*<<< orphan*/  vub300_queue_poll_work (struct vub300_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vub300_enable_sdio_irq(struct mmc_host *mmc, int enable)
{				/* NOT irq */
	struct vub300_mmc_host *vub300 = mmc_priv(mmc);
	if (!vub300->interface)
		return;
	kref_get(&vub300->kref);
	if (enable) {
		mutex_lock(&vub300->irq_mutex);
		if (vub300->irqs_queued) {
			vub300->irqs_queued -= 1;
			mmc_signal_sdio_irq(vub300->mmc);
		} else if (vub300->irq_disabled) {
			vub300->irq_disabled = 0;
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		} else if (vub300->irq_enabled) {
			/* this should not happen, so we will just ignore it */
		} else {
			vub300->irq_enabled = 1;
			vub300_queue_poll_work(vub300, 0);
		}
		mutex_unlock(&vub300->irq_mutex);
	} else {
		vub300->irq_enabled = 0;
	}
	kref_put(&vub300->kref, vub300_delete);
}