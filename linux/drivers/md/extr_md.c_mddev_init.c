#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct mddev {char* last_sync_action; int /*<<< orphan*/  level; void* resync_max; scalar_t__ resync_min; scalar_t__ reshape_backwards; void* reshape_position; int /*<<< orphan*/  recovery_wait; int /*<<< orphan*/  sb_wait; int /*<<< orphan*/  flush_pending; int /*<<< orphan*/  lock; int /*<<< orphan*/  active_io; int /*<<< orphan*/  openers; int /*<<< orphan*/  active; int /*<<< orphan*/  safemode_timer; int /*<<< orphan*/  all_mddevs; int /*<<< orphan*/  disks; TYPE_1__ bitmap_info; int /*<<< orphan*/  reconfig_mutex; int /*<<< orphan*/  open_mutex; int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEVEL_NONE ; 
 void* MaxSector ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_ktype ; 
 int /*<<< orphan*/  md_safemode_timeout ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mddev_init(struct mddev *mddev)
{
	kobject_init(&mddev->kobj, &md_ktype);
	mutex_init(&mddev->open_mutex);
	mutex_init(&mddev->reconfig_mutex);
	mutex_init(&mddev->bitmap_info.mutex);
	INIT_LIST_HEAD(&mddev->disks);
	INIT_LIST_HEAD(&mddev->all_mddevs);
	timer_setup(&mddev->safemode_timer, md_safemode_timeout, 0);
	atomic_set(&mddev->active, 1);
	atomic_set(&mddev->openers, 0);
	atomic_set(&mddev->active_io, 0);
	spin_lock_init(&mddev->lock);
	atomic_set(&mddev->flush_pending, 0);
	init_waitqueue_head(&mddev->sb_wait);
	init_waitqueue_head(&mddev->recovery_wait);
	mddev->reshape_position = MaxSector;
	mddev->reshape_backwards = 0;
	mddev->last_sync_action = "none";
	mddev->resync_min = 0;
	mddev->resync_max = MaxSector;
	mddev->level = LEVEL_NONE;
}