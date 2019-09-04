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
struct uuid_entry {int /*<<< orphan*/  sectors; } ;
struct cache_set {int uuids; } ;
struct bcache_device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  disk; int /*<<< orphan*/  cl; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  add_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_device_attach (struct bcache_device*,struct cache_set*,struct uuid_entry*) ; 
 scalar_t__ bcache_device_init (struct bcache_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcache_device_link (struct bcache_device*,struct cache_set*,char*) ; 
 int /*<<< orphan*/  bch_flash_dev_ktype ; 
 int /*<<< orphan*/  bch_flash_dev_request_init (struct bcache_device*) ; 
 int /*<<< orphan*/  bch_sectors_dirty_init (struct bcache_device*) ; 
 int /*<<< orphan*/  block_bytes (struct cache_set*) ; 
 int /*<<< orphan*/  closure_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* disk_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_dev_flush ; 
 scalar_t__ kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 struct bcache_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_closure_fn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static int flash_dev_run(struct cache_set *c, struct uuid_entry *u)
{
	struct bcache_device *d = kzalloc(sizeof(struct bcache_device),
					  GFP_KERNEL);
	if (!d)
		return -ENOMEM;

	closure_init(&d->cl, NULL);
	set_closure_fn(&d->cl, flash_dev_flush, system_wq);

	kobject_init(&d->kobj, &bch_flash_dev_ktype);

	if (bcache_device_init(d, block_bytes(c), u->sectors))
		goto err;

	bcache_device_attach(d, c, u - c->uuids);
	bch_sectors_dirty_init(d);
	bch_flash_dev_request_init(d);
	add_disk(d->disk);

	if (kobject_add(&d->kobj, &disk_to_dev(d->disk)->kobj, "bcache"))
		goto err;

	bcache_device_link(d, c, "volume");

	return 0;
err:
	kobject_put(&d->kobj);
	return -ENOMEM;
}