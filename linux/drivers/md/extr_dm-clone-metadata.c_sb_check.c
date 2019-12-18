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
typedef  int /*<<< orphan*/  u32 ;
struct superblock_disk {scalar_t__ csum; scalar_t__ version; int /*<<< orphan*/  flags; int /*<<< orphan*/  magic; int /*<<< orphan*/  blocknr; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,scalar_t__,unsigned long long,...) ; 
 int /*<<< orphan*/  DM_CLONE_MAX_METADATA_VERSION ; 
 int /*<<< orphan*/  DM_CLONE_MIN_METADATA_VERSION ; 
 int EILSEQ ; 
 int EINVAL ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  SUPERBLOCK_CSUM_XOR ; 
 scalar_t__ SUPERBLOCK_MAGIC ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct superblock_disk* dm_block_data (struct dm_block*) ; 
 scalar_t__ dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_checksum (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (scalar_t__) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sb_check(struct dm_block_validator *v, struct dm_block *b,
		    size_t sb_block_size)
{
	struct superblock_disk *sb;
	u32 csum, metadata_version;

	sb = dm_block_data(b);

	if (dm_block_location(b) != le64_to_cpu(sb->blocknr)) {
		DMERR("Superblock check failed: blocknr %llu, expected %llu",
		      le64_to_cpu(sb->blocknr),
		      (unsigned long long)dm_block_location(b));
		return -ENOTBLK;
	}

	if (le64_to_cpu(sb->magic) != SUPERBLOCK_MAGIC) {
		DMERR("Superblock check failed: magic %llu, expected %llu",
		      le64_to_cpu(sb->magic),
		      (unsigned long long)SUPERBLOCK_MAGIC);
		return -EILSEQ;
	}

	csum = dm_bm_checksum(&sb->flags, sb_block_size - sizeof(__le32),
			      SUPERBLOCK_CSUM_XOR);
	if (sb->csum != cpu_to_le32(csum)) {
		DMERR("Superblock check failed: checksum %u, expected %u",
		      csum, le32_to_cpu(sb->csum));
		return -EILSEQ;
	}

	/* Check metadata version */
	metadata_version = le32_to_cpu(sb->version);
	if (metadata_version < DM_CLONE_MIN_METADATA_VERSION ||
	    metadata_version > DM_CLONE_MAX_METADATA_VERSION) {
		DMERR("Clone metadata version %u found, but only versions between %u and %u supported.",
		      metadata_version, DM_CLONE_MIN_METADATA_VERSION,
		      DM_CLONE_MAX_METADATA_VERSION);
		return -EINVAL;
	}

	return 0;
}