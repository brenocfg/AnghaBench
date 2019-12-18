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
typedef  int /*<<< orphan*/  uint32_t ;
struct ll_disk {int (* load_ie ) (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ;int /*<<< orphan*/  tm; int /*<<< orphan*/  entries_per_block; } ;
struct dm_block {int dummy; } ;
struct disk_index_entry {int /*<<< orphan*/  blocknr; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bitmap_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_sm_bitmap_validator ; 
 int dm_tm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sm_lookup_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ; 

int sm_ll_lookup_bitmap(struct ll_disk *ll, dm_block_t b, uint32_t *result)
{
	int r;
	dm_block_t index = b;
	struct disk_index_entry ie_disk;
	struct dm_block *blk;

	b = do_div(index, ll->entries_per_block);
	r = ll->load_ie(ll, index, &ie_disk);
	if (r < 0)
		return r;

	r = dm_tm_read_lock(ll->tm, le64_to_cpu(ie_disk.blocknr),
			    &dm_sm_bitmap_validator, &blk);
	if (r < 0)
		return r;

	*result = sm_lookup_bitmap(dm_bitmap_data(blk), b);

	dm_tm_unlock(ll->tm, blk);

	return 0;
}