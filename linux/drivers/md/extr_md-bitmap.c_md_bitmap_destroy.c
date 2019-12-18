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
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct mddev {TYPE_2__* thread; TYPE_1__ bitmap_info; int /*<<< orphan*/  lock; struct bitmap* bitmap; int /*<<< orphan*/ * wb_info_pool; } ;
struct bitmap {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  md_bitmap_free (struct bitmap*) ; 
 int /*<<< orphan*/  md_bitmap_wait_behind_writes (struct mddev*) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void md_bitmap_destroy(struct mddev *mddev)
{
	struct bitmap *bitmap = mddev->bitmap;

	if (!bitmap) /* there was no bitmap */
		return;

	md_bitmap_wait_behind_writes(mddev);
	mempool_destroy(mddev->wb_info_pool);
	mddev->wb_info_pool = NULL;

	mutex_lock(&mddev->bitmap_info.mutex);
	spin_lock(&mddev->lock);
	mddev->bitmap = NULL; /* disconnect from the md device */
	spin_unlock(&mddev->lock);
	mutex_unlock(&mddev->bitmap_info.mutex);
	if (mddev->thread)
		mddev->thread->timeout = MAX_SCHEDULE_TIMEOUT;

	md_bitmap_free(bitmap);
}