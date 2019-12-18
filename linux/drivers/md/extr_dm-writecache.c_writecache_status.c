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
typedef  int uint64_t ;
struct dm_writecache {int n_blocks; char* max_writeback_jobs; char* autocommit_blocks; int /*<<< orphan*/  writeback_fua; int /*<<< orphan*/  writeback_fua_set; int /*<<< orphan*/  autocommit_jiffies; int /*<<< orphan*/  autocommit_time_set; int /*<<< orphan*/  autocommit_blocks_set; int /*<<< orphan*/  max_writeback_jobs_set; int /*<<< orphan*/  freelist_low_watermark; int /*<<< orphan*/  low_wm_percent_set; int /*<<< orphan*/  freelist_high_watermark; int /*<<< orphan*/  high_wm_percent_set; scalar_t__ start_sector; int /*<<< orphan*/  block_size; TYPE_2__* ssd_dev; TYPE_1__* dev; scalar_t__ writeback_size; scalar_t__ freelist_size; } ;
struct dm_target {struct dm_writecache* private; } ;
typedef  int status_type_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 int /*<<< orphan*/  WC_MODE_PMEM (struct dm_writecache*) ; 
 int /*<<< orphan*/  do_div (int,size_t) ; 
 char* jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writecache_has_error (struct dm_writecache*) ; 

__attribute__((used)) static void writecache_status(struct dm_target *ti, status_type_t type,
			      unsigned status_flags, char *result, unsigned maxlen)
{
	struct dm_writecache *wc = ti->private;
	unsigned extra_args;
	unsigned sz = 0;
	uint64_t x;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%ld %llu %llu %llu", writecache_has_error(wc),
		       (unsigned long long)wc->n_blocks, (unsigned long long)wc->freelist_size,
		       (unsigned long long)wc->writeback_size);
		break;
	case STATUSTYPE_TABLE:
		DMEMIT("%c %s %s %u ", WC_MODE_PMEM(wc) ? 'p' : 's',
				wc->dev->name, wc->ssd_dev->name, wc->block_size);
		extra_args = 0;
		if (wc->start_sector)
			extra_args += 2;
		if (wc->high_wm_percent_set)
			extra_args += 2;
		if (wc->low_wm_percent_set)
			extra_args += 2;
		if (wc->max_writeback_jobs_set)
			extra_args += 2;
		if (wc->autocommit_blocks_set)
			extra_args += 2;
		if (wc->autocommit_time_set)
			extra_args += 2;
		if (wc->writeback_fua_set)
			extra_args++;

		DMEMIT("%u", extra_args);
		if (wc->start_sector)
			DMEMIT(" start_sector %llu", (unsigned long long)wc->start_sector);
		if (wc->high_wm_percent_set) {
			x = (uint64_t)wc->freelist_high_watermark * 100;
			x += wc->n_blocks / 2;
			do_div(x, (size_t)wc->n_blocks);
			DMEMIT(" high_watermark %u", 100 - (unsigned)x);
		}
		if (wc->low_wm_percent_set) {
			x = (uint64_t)wc->freelist_low_watermark * 100;
			x += wc->n_blocks / 2;
			do_div(x, (size_t)wc->n_blocks);
			DMEMIT(" low_watermark %u", 100 - (unsigned)x);
		}
		if (wc->max_writeback_jobs_set)
			DMEMIT(" writeback_jobs %u", wc->max_writeback_jobs);
		if (wc->autocommit_blocks_set)
			DMEMIT(" autocommit_blocks %u", wc->autocommit_blocks);
		if (wc->autocommit_time_set)
			DMEMIT(" autocommit_time %u", jiffies_to_msecs(wc->autocommit_jiffies));
		if (wc->writeback_fua_set)
			DMEMIT(" %sfua", wc->writeback_fua ? "" : "no");
		break;
	}
}