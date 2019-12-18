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
typedef  int /*<<< orphan*/  u32 ;
struct uuid_entry {int /*<<< orphan*/  invalidated; int /*<<< orphan*/  uuid; } ;
struct bcache_device {int id; TYPE_1__* c; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  caching; int /*<<< orphan*/ ** devices; struct uuid_entry* uuids; int /*<<< orphan*/  attached_dev_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCACHE_DEV_DETACHING ; 
 int /*<<< orphan*/  SET_UUID_FLASH_ONLY (struct uuid_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcache_device_unlink (struct bcache_device*) ; 
 int /*<<< orphan*/  bch_register_lock ; 
 int /*<<< orphan*/  bch_uuid_write (TYPE_1__*) ; 
 int /*<<< orphan*/  closure_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalid_uuid ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcache_device_detach(struct bcache_device *d)
{
	lockdep_assert_held(&bch_register_lock);

	atomic_dec(&d->c->attached_dev_nr);

	if (test_bit(BCACHE_DEV_DETACHING, &d->flags)) {
		struct uuid_entry *u = d->c->uuids + d->id;

		SET_UUID_FLASH_ONLY(u, 0);
		memcpy(u->uuid, invalid_uuid, 16);
		u->invalidated = cpu_to_le32((u32)ktime_get_real_seconds());
		bch_uuid_write(d->c);
	}

	bcache_device_unlink(d);

	d->c->devices[d->id] = NULL;
	closure_put(&d->c->caching);
	d->c = NULL;
}