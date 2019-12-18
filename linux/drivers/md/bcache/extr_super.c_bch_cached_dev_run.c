#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct closure {int dummy; } ;
struct bcache_device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  disk; int /*<<< orphan*/  c; } ;
struct TYPE_5__ {char* uuid; int /*<<< orphan*/  label; } ;
struct cached_dev {int /*<<< orphan*/  status_update_thread; struct bcache_device disk; int /*<<< orphan*/  bdev; TYPE_2__ sb; int /*<<< orphan*/  backing_dev_name; int /*<<< orphan*/  running; scalar_t__ io_disable; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 scalar_t__ BDEV_STATE (TYPE_2__*) ; 
 scalar_t__ BDEV_STATE_NONE ; 
 int /*<<< orphan*/  BDEV_STATE_STALE ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KOBJ_CHANGE ; 
 int /*<<< orphan*/  SB_LABEL_SIZE ; 
 int /*<<< orphan*/  SET_BDEV_STATE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_disk (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bch_write_bdev_super (struct cached_dev*,struct closure*) ; 
 int /*<<< orphan*/  bd_link_disk_holder (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cached_dev_status_update ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmemdup_nul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct cached_dev*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int bch_cached_dev_run(struct cached_dev *dc)
{
	struct bcache_device *d = &dc->disk;
	char *buf = kmemdup_nul(dc->sb.label, SB_LABEL_SIZE, GFP_KERNEL);
	char *env[] = {
		"DRIVER=bcache",
		kasprintf(GFP_KERNEL, "CACHED_UUID=%pU", dc->sb.uuid),
		kasprintf(GFP_KERNEL, "CACHED_LABEL=%s", buf ? : ""),
		NULL,
	};

	if (dc->io_disable) {
		pr_err("I/O disabled on cached dev %s",
		       dc->backing_dev_name);
		kfree(env[1]);
		kfree(env[2]);
		kfree(buf);
		return -EIO;
	}

	if (atomic_xchg(&dc->running, 1)) {
		kfree(env[1]);
		kfree(env[2]);
		kfree(buf);
		pr_info("cached dev %s is running already",
		       dc->backing_dev_name);
		return -EBUSY;
	}

	if (!d->c &&
	    BDEV_STATE(&dc->sb) != BDEV_STATE_NONE) {
		struct closure cl;

		closure_init_stack(&cl);

		SET_BDEV_STATE(&dc->sb, BDEV_STATE_STALE);
		bch_write_bdev_super(dc, &cl);
		closure_sync(&cl);
	}

	add_disk(d->disk);
	bd_link_disk_holder(dc->bdev, dc->disk.disk);
	/*
	 * won't show up in the uevent file, use udevadm monitor -e instead
	 * only class / kset properties are persistent
	 */
	kobject_uevent_env(&disk_to_dev(d->disk)->kobj, KOBJ_CHANGE, env);
	kfree(env[1]);
	kfree(env[2]);
	kfree(buf);

	if (sysfs_create_link(&d->kobj, &disk_to_dev(d->disk)->kobj, "dev") ||
	    sysfs_create_link(&disk_to_dev(d->disk)->kobj,
			      &d->kobj, "bcache")) {
		pr_err("Couldn't create bcache dev <-> disk sysfs symlinks");
		return -ENOMEM;
	}

	dc->status_update_thread = kthread_run(cached_dev_status_update,
					       dc, "bcache_status_update");
	if (IS_ERR(dc->status_update_thread)) {
		pr_warn("failed to create bcache_status_update kthread, "
			"continue to run without monitoring backing "
			"device status");
	}

	return 0;
}