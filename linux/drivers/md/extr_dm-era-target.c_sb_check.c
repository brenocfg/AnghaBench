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
struct superblock_disk {scalar_t__ csum; int /*<<< orphan*/  flags; int /*<<< orphan*/  magic; int /*<<< orphan*/  blocknr; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,unsigned long long,unsigned long long) ; 
 int EILSEQ ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  SUPERBLOCK_CSUM_XOR ; 
 scalar_t__ SUPERBLOCK_MAGIC ; 
 int check_metadata_version (struct superblock_disk*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct superblock_disk* dm_block_data (struct dm_block*) ; 
 scalar_t__ dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 unsigned long long le32_to_cpu (scalar_t__) ; 
 unsigned long long le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sb_check(struct dm_block_validator *v,
		    struct dm_block *b,
		    size_t sb_block_size)
{
	struct superblock_disk *disk = dm_block_data(b);
	__le32 csum_le;

	if (dm_block_location(b) != le64_to_cpu(disk->blocknr)) {
		DMERR("sb_check failed: blocknr %llu: wanted %llu",
		      le64_to_cpu(disk->blocknr),
		      (unsigned long long)dm_block_location(b));
		return -ENOTBLK;
	}

	if (le64_to_cpu(disk->magic) != SUPERBLOCK_MAGIC) {
		DMERR("sb_check failed: magic %llu: wanted %llu",
		      le64_to_cpu(disk->magic),
		      (unsigned long long) SUPERBLOCK_MAGIC);
		return -EILSEQ;
	}

	csum_le = cpu_to_le32(dm_bm_checksum(&disk->flags,
					     sb_block_size - sizeof(__le32),
					     SUPERBLOCK_CSUM_XOR));
	if (csum_le != disk->csum) {
		DMERR("sb_check failed: csum %u: wanted %u",
		      le32_to_cpu(csum_le), le32_to_cpu(disk->csum));
		return -EILSEQ;
	}

	return check_metadata_version(disk);
}