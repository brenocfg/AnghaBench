#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drbd_device {struct drbd_bitmap* bitmap; } ;
struct drbd_bitmap {char* bm_why; int bm_flags; TYPE_1__* bm_task; int /*<<< orphan*/  bm_change; } ;
typedef  enum bm_flag { ____Placeholder_bm_flag } bm_flag ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int BM_LOCKED_MASK ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*) ; 
 int /*<<< orphan*/  drbd_warn (struct drbd_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

void drbd_bm_lock(struct drbd_device *device, char *why, enum bm_flag flags)
{
	struct drbd_bitmap *b = device->bitmap;
	int trylock_failed;

	if (!b) {
		drbd_err(device, "FIXME no bitmap in drbd_bm_lock!?\n");
		return;
	}

	trylock_failed = !mutex_trylock(&b->bm_change);

	if (trylock_failed) {
		drbd_warn(device, "%s[%d] going to '%s' but bitmap already locked for '%s' by %s[%d]\n",
			  current->comm, task_pid_nr(current),
			  why, b->bm_why ?: "?",
			  b->bm_task->comm, task_pid_nr(b->bm_task));
		mutex_lock(&b->bm_change);
	}
	if (BM_LOCKED_MASK & b->bm_flags)
		drbd_err(device, "FIXME bitmap already locked in bm_lock\n");
	b->bm_flags |= flags & BM_LOCKED_MASK;

	b->bm_why  = why;
	b->bm_task = current;
}