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
struct ww_acquire_ctx {int dummy; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ww_acquire_fini (struct ww_acquire_ctx*) ; 

void
drm_gem_unlock_reservations(struct drm_gem_object **objs, int count,
			    struct ww_acquire_ctx *acquire_ctx)
{
	int i;

	for (i = 0; i < count; i++)
		dma_resv_unlock(objs[i]->resv);

	ww_acquire_fini(acquire_ctx);
}