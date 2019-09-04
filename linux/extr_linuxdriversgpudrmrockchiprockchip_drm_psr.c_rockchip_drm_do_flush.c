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
struct psr_drv {int /*<<< orphan*/  lock; int /*<<< orphan*/  flush_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_FLUSH_TIMEOUT_MS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_set_state_locked (struct psr_drv*,int) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void rockchip_drm_do_flush(struct psr_drv *psr)
{
	cancel_delayed_work_sync(&psr->flush_work);

	mutex_lock(&psr->lock);
	if (!psr_set_state_locked(psr, false))
		mod_delayed_work(system_wq, &psr->flush_work,
				 PSR_FLUSH_TIMEOUT_MS);
	mutex_unlock(&psr->lock);
}