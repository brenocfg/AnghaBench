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
struct dm_block_manager {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  scalar_t__ __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  SUPERBLOCK_LOCATION ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 scalar_t__* dm_block_data (struct dm_block*) ; 
 int dm_bm_block_size (struct dm_block_manager*) ; 
 int dm_bm_read_lock (struct dm_block_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 

__attribute__((used)) static int __superblock_all_zeroes(struct dm_block_manager *bm, bool *formatted)
{
	int r;
	unsigned int i, nr_words;
	struct dm_block *sblock;
	__le64 *data_le, zero = cpu_to_le64(0);

	/*
	 * We don't use a validator here because the superblock could be all
	 * zeroes.
	 */
	r = dm_bm_read_lock(bm, SUPERBLOCK_LOCATION, NULL, &sblock);
	if (r) {
		DMERR("Failed to read_lock superblock");
		return r;
	}

	data_le = dm_block_data(sblock);
	*formatted = false;

	/* This assumes that the block size is a multiple of 8 bytes */
	BUG_ON(dm_bm_block_size(bm) % sizeof(__le64));
	nr_words = dm_bm_block_size(bm) / sizeof(__le64);
	for (i = 0; i < nr_words; i++) {
		if (data_le[i] != zero) {
			*formatted = true;
			break;
		}
	}

	dm_bm_unlock(sblock);

	return 0;
}