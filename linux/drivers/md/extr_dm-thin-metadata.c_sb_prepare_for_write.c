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
struct thin_disk_superblock {int /*<<< orphan*/  flags; int /*<<< orphan*/  csum; int /*<<< orphan*/  blocknr; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SUPERBLOCK_CSUM_XOR ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct thin_disk_superblock* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sb_prepare_for_write(struct dm_block_validator *v,
				 struct dm_block *b,
				 size_t block_size)
{
	struct thin_disk_superblock *disk_super = dm_block_data(b);

	disk_super->blocknr = cpu_to_le64(dm_block_location(b));
	disk_super->csum = cpu_to_le32(dm_bm_checksum(&disk_super->flags,
						      block_size - sizeof(__le32),
						      SUPERBLOCK_CSUM_XOR));
}