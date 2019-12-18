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
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
struct disk_bitmap_header {int /*<<< orphan*/  not_used; int /*<<< orphan*/  csum; int /*<<< orphan*/  blocknr; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_CSUM_XOR ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct disk_bitmap_header* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_bitmap_prepare_for_write(struct dm_block_validator *v,
					struct dm_block *b,
					size_t block_size)
{
	struct disk_bitmap_header *disk_header = dm_block_data(b);

	disk_header->blocknr = cpu_to_le64(dm_block_location(b));
	disk_header->csum = cpu_to_le32(dm_bm_checksum(&disk_header->not_used,
						       block_size - sizeof(__le32),
						       BITMAP_CSUM_XOR));
}