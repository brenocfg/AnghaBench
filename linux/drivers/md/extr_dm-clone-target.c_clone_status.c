#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct clone* private; } ;
struct clone {unsigned int nr_ctr_args; int /*<<< orphan*/ * ctr_args; TYPE_6__* source_dev; TYPE_4__* dest_dev; TYPE_2__* metadata_dev; int /*<<< orphan*/  hydrations_in_flight; int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  cmd; scalar_t__ region_size; } ;
typedef  int status_type_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_12__ {TYPE_5__* bdev; } ;
struct TYPE_11__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_10__ {TYPE_3__* bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_8__ {TYPE_1__* bdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
#define  CM_FAIL 132 
#define  CM_READ_ONLY 131 
#define  CM_WRITE 130 
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DM_CLONE_METADATA_BLOCK_SIZE ; 
 unsigned int DM_STATUS_NOFLUSH_FLAG ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clone_device_name (struct clone*) ; 
 int /*<<< orphan*/  commit_metadata (struct clone*) ; 
 int dm_clone_get_free_metadata_block_count (int /*<<< orphan*/ ,scalar_t__*) ; 
 int dm_clone_get_metadata_dev_size (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dm_clone_nr_of_hydrated_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_suspended (struct dm_target*) ; 
 int /*<<< orphan*/  emit_core_args (struct clone*,char*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_flags (struct clone*,char*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  format_dev_t (char*,int /*<<< orphan*/ ) ; 
 int get_clone_mode (struct clone*) ; 

__attribute__((used)) static void clone_status(struct dm_target *ti, status_type_t type,
			 unsigned int status_flags, char *result,
			 unsigned int maxlen)
{
	int r;
	unsigned int i;
	ssize_t sz = 0;
	dm_block_t nr_free_metadata_blocks = 0;
	dm_block_t nr_metadata_blocks = 0;
	char buf[BDEVNAME_SIZE];
	struct clone *clone = ti->private;

	switch (type) {
	case STATUSTYPE_INFO:
		if (get_clone_mode(clone) == CM_FAIL) {
			DMEMIT("Fail");
			break;
		}

		/* Commit to ensure statistics aren't out-of-date */
		if (!(status_flags & DM_STATUS_NOFLUSH_FLAG) && !dm_suspended(ti))
			(void) commit_metadata(clone);

		r = dm_clone_get_free_metadata_block_count(clone->cmd, &nr_free_metadata_blocks);

		if (r) {
			DMERR("%s: dm_clone_get_free_metadata_block_count returned %d",
			      clone_device_name(clone), r);
			goto error;
		}

		r = dm_clone_get_metadata_dev_size(clone->cmd, &nr_metadata_blocks);

		if (r) {
			DMERR("%s: dm_clone_get_metadata_dev_size returned %d",
			      clone_device_name(clone), r);
			goto error;
		}

		DMEMIT("%u %llu/%llu %llu %lu/%lu %u ",
		       DM_CLONE_METADATA_BLOCK_SIZE,
		       (unsigned long long)(nr_metadata_blocks - nr_free_metadata_blocks),
		       (unsigned long long)nr_metadata_blocks,
		       (unsigned long long)clone->region_size,
		       dm_clone_nr_of_hydrated_regions(clone->cmd),
		       clone->nr_regions,
		       atomic_read(&clone->hydrations_in_flight));

		emit_flags(clone, result, maxlen, &sz);
		emit_core_args(clone, result, maxlen, &sz);

		switch (get_clone_mode(clone)) {
		case CM_WRITE:
			DMEMIT("rw");
			break;
		case CM_READ_ONLY:
			DMEMIT("ro");
			break;
		case CM_FAIL:
			DMEMIT("Fail");
		}

		break;

	case STATUSTYPE_TABLE:
		format_dev_t(buf, clone->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		format_dev_t(buf, clone->dest_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);

		format_dev_t(buf, clone->source_dev->bdev->bd_dev);
		DMEMIT("%s", buf);

		for (i = 0; i < clone->nr_ctr_args; i++)
			DMEMIT(" %s", clone->ctr_args[i]);
	}

	return;

error:
	DMEMIT("Error");
}