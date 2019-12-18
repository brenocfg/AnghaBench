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
 int EDEADLK ; 
 int dma_resv_lock_interruptible (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int dma_resv_lock_slow_interruptible (int /*<<< orphan*/ ,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_ww_class ; 
 int /*<<< orphan*/  ww_acquire_done (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_acquire_init (struct ww_acquire_ctx*,int /*<<< orphan*/ *) ; 

int
drm_gem_lock_reservations(struct drm_gem_object **objs, int count,
			  struct ww_acquire_ctx *acquire_ctx)
{
	int contended = -1;
	int i, ret;

	ww_acquire_init(acquire_ctx, &reservation_ww_class);

retry:
	if (contended != -1) {
		struct drm_gem_object *obj = objs[contended];

		ret = dma_resv_lock_slow_interruptible(obj->resv,
								 acquire_ctx);
		if (ret) {
			ww_acquire_done(acquire_ctx);
			return ret;
		}
	}

	for (i = 0; i < count; i++) {
		if (i == contended)
			continue;

		ret = dma_resv_lock_interruptible(objs[i]->resv,
							    acquire_ctx);
		if (ret) {
			int j;

			for (j = 0; j < i; j++)
				dma_resv_unlock(objs[j]->resv);

			if (contended != -1 && contended >= i)
				dma_resv_unlock(objs[contended]->resv);

			if (ret == -EDEADLK) {
				contended = i;
				goto retry;
			}

			ww_acquire_done(acquire_ctx);
			return ret;
		}
	}

	ww_acquire_done(acquire_ctx);

	return 0;
}