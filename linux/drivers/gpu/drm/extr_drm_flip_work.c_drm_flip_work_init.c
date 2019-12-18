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
struct drm_flip_work {char const* name; int /*<<< orphan*/  worker; int /*<<< orphan*/  func; int /*<<< orphan*/  lock; int /*<<< orphan*/  commited; int /*<<< orphan*/  queued; } ;
typedef  int /*<<< orphan*/  drm_flip_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flip_worker ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void drm_flip_work_init(struct drm_flip_work *work,
		const char *name, drm_flip_func_t func)
{
	work->name = name;
	INIT_LIST_HEAD(&work->queued);
	INIT_LIST_HEAD(&work->commited);
	spin_lock_init(&work->lock);
	work->func = func;

	INIT_WORK(&work->worker, flip_worker);
}