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
struct psr_drv {scalar_t__ inhibit_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  flush_work; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct psr_drv*) ; 
 int /*<<< orphan*/  PSR_FLUSH_TIMEOUT_MS ; 
 int PTR_ERR (struct psr_drv*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct psr_drv* find_psr_by_encoder (struct drm_encoder*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_wq ; 

int rockchip_drm_psr_inhibit_put(struct drm_encoder *encoder)
{
	struct psr_drv *psr = find_psr_by_encoder(encoder);

	if (IS_ERR(psr))
		return PTR_ERR(psr);

	mutex_lock(&psr->lock);
	--psr->inhibit_count;
	WARN_ON(psr->inhibit_count < 0);
	if (!psr->inhibit_count)
		mod_delayed_work(system_wq, &psr->flush_work,
				 PSR_FLUSH_TIMEOUT_MS);
	mutex_unlock(&psr->lock);

	return 0;
}