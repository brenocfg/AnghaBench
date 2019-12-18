#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ww_acquire_ctx {int dummy; } ;
struct TYPE_4__ {TYPE_1__* resv; } ;
struct lima_bo {TYPE_2__ gem; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  reservation_ww_class ; 
 int /*<<< orphan*/  ww_acquire_done (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_acquire_fini (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_acquire_init (struct ww_acquire_ctx*,int /*<<< orphan*/ *) ; 
 int ww_mutex_lock_interruptible (int /*<<< orphan*/ *,struct ww_acquire_ctx*) ; 
 int ww_mutex_lock_slow_interruptible (int /*<<< orphan*/ *,struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lima_gem_lock_bos(struct lima_bo **bos, u32 nr_bos,
			     struct ww_acquire_ctx *ctx)
{
	int i, ret = 0, contended, slow_locked = -1;

	ww_acquire_init(ctx, &reservation_ww_class);

retry:
	for (i = 0; i < nr_bos; i++) {
		if (i == slow_locked) {
			slow_locked = -1;
			continue;
		}

		ret = ww_mutex_lock_interruptible(&bos[i]->gem.resv->lock, ctx);
		if (ret < 0) {
			contended = i;
			goto err;
		}
	}

	ww_acquire_done(ctx);
	return 0;

err:
	for (i--; i >= 0; i--)
		ww_mutex_unlock(&bos[i]->gem.resv->lock);

	if (slow_locked >= 0)
		ww_mutex_unlock(&bos[slow_locked]->gem.resv->lock);

	if (ret == -EDEADLK) {
		/* we lost out in a seqno race, lock and retry.. */
		ret = ww_mutex_lock_slow_interruptible(
			&bos[contended]->gem.resv->lock, ctx);
		if (!ret) {
			slow_locked = contended;
			goto retry;
		}
	}
	ww_acquire_fini(ctx);

	return ret;
}