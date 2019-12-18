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
typedef  int /*<<< orphan*/  uint32_t ;
struct mirror_set {unsigned int nr_mirrors; int /*<<< orphan*/  io_client; int /*<<< orphan*/  rh; int /*<<< orphan*/  nr_regions; struct dm_target* ti; int /*<<< orphan*/  default_mirror; int /*<<< orphan*/  suspend; scalar_t__ leg_failure; scalar_t__ log_failure; scalar_t__ in_sync; int /*<<< orphan*/  holds; int /*<<< orphan*/  failures; int /*<<< orphan*/  writes; int /*<<< orphan*/  reads; int /*<<< orphan*/  lock; } ;
struct dm_target {char* error; int /*<<< orphan*/  begin; int /*<<< orphan*/  len; } ;
struct dm_dirty_log {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_MIRROR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_RECOVERY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dispatch_bios ; 
 int /*<<< orphan*/  dm_io_client_create () ; 
 int /*<<< orphan*/  dm_io_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_region_hash_create (struct mirror_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_sector_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mirror_set*) ; 
 struct mirror_set* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mirror ; 
 struct mirror_set* ms ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wakeup_all_recovery_waiters ; 
 int /*<<< orphan*/  wakeup_mirrord ; 

__attribute__((used)) static struct mirror_set *alloc_context(unsigned int nr_mirrors,
					uint32_t region_size,
					struct dm_target *ti,
					struct dm_dirty_log *dl)
{
	struct mirror_set *ms =
		kzalloc(struct_size(ms, mirror, nr_mirrors), GFP_KERNEL);

	if (!ms) {
		ti->error = "Cannot allocate mirror context";
		return NULL;
	}

	spin_lock_init(&ms->lock);
	bio_list_init(&ms->reads);
	bio_list_init(&ms->writes);
	bio_list_init(&ms->failures);
	bio_list_init(&ms->holds);

	ms->ti = ti;
	ms->nr_mirrors = nr_mirrors;
	ms->nr_regions = dm_sector_div_up(ti->len, region_size);
	ms->in_sync = 0;
	ms->log_failure = 0;
	ms->leg_failure = 0;
	atomic_set(&ms->suspend, 0);
	atomic_set(&ms->default_mirror, DEFAULT_MIRROR);

	ms->io_client = dm_io_client_create();
	if (IS_ERR(ms->io_client)) {
		ti->error = "Error creating dm_io client";
		kfree(ms);
 		return NULL;
	}

	ms->rh = dm_region_hash_create(ms, dispatch_bios, wakeup_mirrord,
				       wakeup_all_recovery_waiters,
				       ms->ti->begin, MAX_RECOVERY,
				       dl, region_size, ms->nr_regions);
	if (IS_ERR(ms->rh)) {
		ti->error = "Error creating dirty region hash";
		dm_io_client_destroy(ms->io_client);
		kfree(ms);
		return NULL;
	}

	return ms;
}