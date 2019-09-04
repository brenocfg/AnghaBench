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
struct superblock_disk {void* metadata_snap; void* era_array_root; void* writeset_tree_root; int /*<<< orphan*/  current_writeset; void* current_era; void* nr_blocks; void* metadata_block_size; void* data_block_size; void* version; int /*<<< orphan*/  uuid; void* flags; void* magic; } ;
struct era_metadata {unsigned long block_size; unsigned long nr_blocks; unsigned long current_era; int /*<<< orphan*/  metadata_snap; int /*<<< orphan*/  era_array_root; int /*<<< orphan*/  writeset_tree_root; TYPE_1__* current_writeset; } ;
struct TYPE_2__ {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 unsigned long DM_ERA_METADATA_BLOCK_SIZE ; 
 unsigned long MAX_ERA_VERSION ; 
 unsigned long SECTOR_SHIFT ; 
 int /*<<< orphan*/  SUPERBLOCK_MAGIC ; 
 int /*<<< orphan*/  copy_sm_root (struct era_metadata*,struct superblock_disk*) ; 
 void* cpu_to_le32 (unsigned long) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ws_pack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_superblock(struct era_metadata *md, struct superblock_disk *disk)
{
	disk->magic = cpu_to_le64(SUPERBLOCK_MAGIC);
	disk->flags = cpu_to_le32(0ul);

	/* FIXME: can't keep blanking the uuid (uuid is currently unused though) */
	memset(disk->uuid, 0, sizeof(disk->uuid));
	disk->version = cpu_to_le32(MAX_ERA_VERSION);

	copy_sm_root(md, disk);

	disk->data_block_size = cpu_to_le32(md->block_size);
	disk->metadata_block_size = cpu_to_le32(DM_ERA_METADATA_BLOCK_SIZE >> SECTOR_SHIFT);
	disk->nr_blocks = cpu_to_le32(md->nr_blocks);
	disk->current_era = cpu_to_le32(md->current_era);

	ws_pack(&md->current_writeset->md, &disk->current_writeset);
	disk->writeset_tree_root = cpu_to_le64(md->writeset_tree_root);
	disk->era_array_root = cpu_to_le64(md->era_array_root);
	disk->metadata_snap = cpu_to_le64(md->metadata_snap);
}