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
struct cache_sb {unsigned int first_bucket; unsigned int keys; void* seq; void* flags; void* version; int /*<<< orphan*/  csum; void** d; int /*<<< orphan*/  last_mount; int /*<<< orphan*/  label; int /*<<< orphan*/  set_uuid; int /*<<< orphan*/  uuid; void* offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; int /*<<< orphan*/  bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 int SB_LABEL_SIZE ; 
 int /*<<< orphan*/  SB_SECTOR ; 
 int /*<<< orphan*/  SB_SIZE ; 
 int /*<<< orphan*/  bch_bio_map (struct bio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_first_page_all (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (void*) ; 
 int /*<<< orphan*/  csum_set (struct cache_sb*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cache_sb* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,void*,void*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 

__attribute__((used)) static void __write_super(struct cache_sb *sb, struct bio *bio)
{
	struct cache_sb *out = page_address(bio_first_page_all(bio));
	unsigned int i;

	bio->bi_iter.bi_sector	= SB_SECTOR;
	bio->bi_iter.bi_size	= SB_SIZE;
	bio_set_op_attrs(bio, REQ_OP_WRITE, REQ_SYNC|REQ_META);
	bch_bio_map(bio, NULL);

	out->offset		= cpu_to_le64(sb->offset);
	out->version		= cpu_to_le64(sb->version);

	memcpy(out->uuid,	sb->uuid, 16);
	memcpy(out->set_uuid,	sb->set_uuid, 16);
	memcpy(out->label,	sb->label, SB_LABEL_SIZE);

	out->flags		= cpu_to_le64(sb->flags);
	out->seq		= cpu_to_le64(sb->seq);

	out->last_mount		= cpu_to_le32(sb->last_mount);
	out->first_bucket	= cpu_to_le16(sb->first_bucket);
	out->keys		= cpu_to_le16(sb->keys);

	for (i = 0; i < sb->keys; i++)
		out->d[i] = cpu_to_le64(sb->d[i]);

	out->csum = csum_set(out);

	pr_debug("ver %llu, flags %llu, seq %llu",
		 sb->version, sb->flags, sb->seq);

	submit_bio(bio);
}