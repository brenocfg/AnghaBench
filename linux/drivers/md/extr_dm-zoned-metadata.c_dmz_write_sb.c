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
typedef  scalar_t__ u64 ;
struct dmz_super {void* crc; void* nr_bitmap_blocks; void* nr_map_blocks; void* nr_chunks; void* nr_reserved_seq; void* nr_meta_blocks; void* sb_block; void* gen; void* version; void* magic; } ;
struct dmz_metadata {TYPE_2__* dev; int /*<<< orphan*/  nr_bitmap_blocks; int /*<<< orphan*/  nr_map_blocks; int /*<<< orphan*/  nr_chunks; int /*<<< orphan*/  nr_reserved_seq; int /*<<< orphan*/  nr_meta_blocks; scalar_t__ sb_gen; TYPE_1__* sb; } ;
struct dmz_mblock {int /*<<< orphan*/  page; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {struct dmz_super* sb; struct dmz_mblock* mblk; scalar_t__ block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMZ_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMZ_MAGIC ; 
 int /*<<< orphan*/  DMZ_META_VER ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int blkdev_issue_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  crc32_le (scalar_t__,unsigned char*,int /*<<< orphan*/ ) ; 
 int dmz_rdwr_block (struct dmz_metadata*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmz_write_sb(struct dmz_metadata *zmd, unsigned int set)
{
	sector_t block = zmd->sb[set].block;
	struct dmz_mblock *mblk = zmd->sb[set].mblk;
	struct dmz_super *sb = zmd->sb[set].sb;
	u64 sb_gen = zmd->sb_gen + 1;
	int ret;

	sb->magic = cpu_to_le32(DMZ_MAGIC);
	sb->version = cpu_to_le32(DMZ_META_VER);

	sb->gen = cpu_to_le64(sb_gen);

	sb->sb_block = cpu_to_le64(block);
	sb->nr_meta_blocks = cpu_to_le32(zmd->nr_meta_blocks);
	sb->nr_reserved_seq = cpu_to_le32(zmd->nr_reserved_seq);
	sb->nr_chunks = cpu_to_le32(zmd->nr_chunks);

	sb->nr_map_blocks = cpu_to_le32(zmd->nr_map_blocks);
	sb->nr_bitmap_blocks = cpu_to_le32(zmd->nr_bitmap_blocks);

	sb->crc = 0;
	sb->crc = cpu_to_le32(crc32_le(sb_gen, (unsigned char *)sb, DMZ_BLOCK_SIZE));

	ret = dmz_rdwr_block(zmd, REQ_OP_WRITE, block, mblk->page);
	if (ret == 0)
		ret = blkdev_issue_flush(zmd->dev->bdev, GFP_NOIO, NULL);

	return ret;
}