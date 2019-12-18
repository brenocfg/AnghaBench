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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u32 ;
struct uuid_entry {int sectors; int /*<<< orphan*/  last_reg; int /*<<< orphan*/  first_reg; int /*<<< orphan*/  label; int /*<<< orphan*/  uuid; } ;
struct cache_set {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_RUNNING ; 
 int /*<<< orphan*/  CACHE_SET_STOPPING ; 
 int EINTR ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  SET_UUID_FLASH_ONLY (struct uuid_entry*,int) ; 
 int /*<<< orphan*/  bch_uuid_write (struct cache_set*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int flash_dev_run (struct cache_set*,struct uuid_entry*) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct uuid_entry* uuid_find_empty (struct cache_set*) ; 

int bch_flash_dev_create(struct cache_set *c, uint64_t size)
{
	struct uuid_entry *u;

	if (test_bit(CACHE_SET_STOPPING, &c->flags))
		return -EINTR;

	if (!test_bit(CACHE_SET_RUNNING, &c->flags))
		return -EPERM;

	u = uuid_find_empty(c);
	if (!u) {
		pr_err("Can't create volume, no room for UUID");
		return -EINVAL;
	}

	get_random_bytes(u->uuid, 16);
	memset(u->label, 0, 32);
	u->first_reg = u->last_reg = cpu_to_le32((u32)ktime_get_real_seconds());

	SET_UUID_FLASH_ONLY(u, 1);
	u->sectors = size >> 9;

	bch_uuid_write(c);

	return flash_dev_run(c, u);
}