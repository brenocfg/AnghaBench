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
struct ll_disk {int /*<<< orphan*/  tm; int /*<<< orphan*/  mi_le; int /*<<< orphan*/  bitmap_root; } ;
struct dm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_block_data (struct dm_block*) ; 
 int dm_tm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int /*<<< orphan*/  dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int /*<<< orphan*/  index_validator ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int metadata_ll_open(struct ll_disk *ll)
{
	int r;
	struct dm_block *block;

	r = dm_tm_read_lock(ll->tm, ll->bitmap_root,
			    &index_validator, &block);
	if (r)
		return r;

	memcpy(&ll->mi_le, dm_block_data(block), sizeof(ll->mi_le));
	dm_tm_unlock(ll->tm, block);

	return 0;
}