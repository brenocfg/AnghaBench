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
struct dm_target {scalar_t__ private; } ;
struct TYPE_12__ {unsigned int key_string; int /*<<< orphan*/  alg_string; } ;
struct TYPE_11__ {unsigned int key_string; int /*<<< orphan*/  alg_string; } ;
struct TYPE_10__ {unsigned int key_string; int /*<<< orphan*/  alg_string; } ;
struct dm_integrity_c {int journal_entries; int free_sectors_threshold; int sectors_per_block; unsigned int initial_sectors; unsigned int log2_buffer_sectors; unsigned int autocommit_msec; TYPE_6__ journal_mac_alg; TYPE_5__ journal_crypt_alg; TYPE_4__ internal_hash_alg; TYPE_3__* sb; TYPE_2__* meta_dev; int /*<<< orphan*/  mode; int /*<<< orphan*/  tag_size; scalar_t__ start; TYPE_1__* dev; scalar_t__ provided_data_sectors; int /*<<< orphan*/  number_of_mismatches; } ;
typedef  int status_type_t ;
typedef  int __u64 ;
struct TYPE_9__ {int flags; unsigned int log2_interleave_sectors; int /*<<< orphan*/  recalc_sector; } ;
struct TYPE_8__ {unsigned int name; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  SB_FLAG_RECALCULATING ; 
 unsigned int SB_SECTORS ; 
 unsigned int SECTOR_SHIFT ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_integrity_status(struct dm_target *ti, status_type_t type,
				unsigned status_flags, char *result, unsigned maxlen)
{
	struct dm_integrity_c *ic = (struct dm_integrity_c *)ti->private;
	unsigned arg_count;
	size_t sz = 0;

	switch (type) {
	case STATUSTYPE_INFO:
		DMEMIT("%llu %llu",
			(unsigned long long)atomic64_read(&ic->number_of_mismatches),
			(unsigned long long)ic->provided_data_sectors);
		if (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
			DMEMIT(" %llu", (unsigned long long)le64_to_cpu(ic->sb->recalc_sector));
		else
			DMEMIT(" -");
		break;

	case STATUSTYPE_TABLE: {
		__u64 watermark_percentage = (__u64)(ic->journal_entries - ic->free_sectors_threshold) * 100;
		watermark_percentage += ic->journal_entries / 2;
		do_div(watermark_percentage, ic->journal_entries);
		arg_count = 5;
		arg_count += !!ic->meta_dev;
		arg_count += ic->sectors_per_block != 1;
		arg_count += !!(ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING));
		arg_count += !!ic->internal_hash_alg.alg_string;
		arg_count += !!ic->journal_crypt_alg.alg_string;
		arg_count += !!ic->journal_mac_alg.alg_string;
		DMEMIT("%s %llu %u %c %u", ic->dev->name, (unsigned long long)ic->start,
		       ic->tag_size, ic->mode, arg_count);
		if (ic->meta_dev)
			DMEMIT(" meta_device:%s", ic->meta_dev->name);
		if (ic->sectors_per_block != 1)
			DMEMIT(" block_size:%u", ic->sectors_per_block << SECTOR_SHIFT);
		if (ic->sb->flags & cpu_to_le32(SB_FLAG_RECALCULATING))
			DMEMIT(" recalculate");
		DMEMIT(" journal_sectors:%u", ic->initial_sectors - SB_SECTORS);
		DMEMIT(" interleave_sectors:%u", 1U << ic->sb->log2_interleave_sectors);
		DMEMIT(" buffer_sectors:%u", 1U << ic->log2_buffer_sectors);
		DMEMIT(" journal_watermark:%u", (unsigned)watermark_percentage);
		DMEMIT(" commit_time:%u", ic->autocommit_msec);

#define EMIT_ALG(a, n)							\
		do {							\
			if (ic->a.alg_string) {				\
				DMEMIT(" %s:%s", n, ic->a.alg_string);	\
				if (ic->a.key_string)			\
					DMEMIT(":%s", ic->a.key_string);\
			}						\
		} while (0)
		EMIT_ALG(internal_hash_alg, "internal_hash");
		EMIT_ALG(journal_crypt_alg, "journal_crypt");
		EMIT_ALG(journal_mac_alg, "journal_mac");
		break;
	}
	}
}