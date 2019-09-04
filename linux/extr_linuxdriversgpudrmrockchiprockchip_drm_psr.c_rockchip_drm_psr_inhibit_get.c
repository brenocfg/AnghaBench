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
struct psr_drv {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  inhibit_count; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct psr_drv*) ; 
 int PTR_ERR (struct psr_drv*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct psr_drv* find_psr_by_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psr_set_state_locked (struct psr_drv*,int) ; 

int rockchip_drm_psr_inhibit_get(struct drm_encoder *encoder)
{
	struct psr_drv *psr = find_psr_by_encoder(encoder);

	if (IS_ERR(psr))
		return PTR_ERR(psr);

	mutex_lock(&psr->lock);
	psr_set_state_locked(psr, false);
	++psr->inhibit_count;
	mutex_unlock(&psr->lock);
	cancel_delayed_work_sync(&psr->flush_work);

	return 0;
}