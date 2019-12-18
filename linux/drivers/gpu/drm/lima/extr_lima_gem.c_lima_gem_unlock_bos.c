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
 int /*<<< orphan*/  ww_acquire_fini (struct ww_acquire_ctx*) ; 
 int /*<<< orphan*/  ww_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lima_gem_unlock_bos(struct lima_bo **bos, u32 nr_bos,
				struct ww_acquire_ctx *ctx)
{
	int i;

	for (i = 0; i < nr_bos; i++)
		ww_mutex_unlock(&bos[i]->gem.resv->lock);
	ww_acquire_fini(ctx);
}