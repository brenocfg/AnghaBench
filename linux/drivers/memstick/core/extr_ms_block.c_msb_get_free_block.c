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
typedef  int u16 ;
struct msb_data {int* free_block_count; int read_only; int block_count; int /*<<< orphan*/  used_blocks_bitmap; } ;
typedef  int /*<<< orphan*/  pos ;

/* Variables and functions */
 int MS_BLOCKS_IN_ZONE ; 
 int MS_BLOCK_INVALID ; 
 int /*<<< orphan*/  dbg_verbose (char*,int,...) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int msb_get_zone_from_pba (int) ; 
 int /*<<< orphan*/  msb_mark_block_used (struct msb_data*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static u16 msb_get_free_block(struct msb_data *msb, int zone)
{
	u16 pos;
	int pba = zone * MS_BLOCKS_IN_ZONE;
	int i;

	get_random_bytes(&pos, sizeof(pos));

	if (!msb->free_block_count[zone]) {
		pr_err("NO free blocks in the zone %d, to use for a write, (media is WORN out) switching to RO mode", zone);
		msb->read_only = true;
		return MS_BLOCK_INVALID;
	}

	pos %= msb->free_block_count[zone];

	dbg_verbose("have %d choices for a free block, selected randomly: %d",
		msb->free_block_count[zone], pos);

	pba = find_next_zero_bit(msb->used_blocks_bitmap,
							msb->block_count, pba);
	for (i = 0; i < pos; ++i)
		pba = find_next_zero_bit(msb->used_blocks_bitmap,
						msb->block_count, pba + 1);

	dbg_verbose("result of the free blocks scan: pba %d", pba);

	if (pba == msb->block_count || (msb_get_zone_from_pba(pba)) != zone) {
		pr_err("BUG: cant get a free block");
		msb->read_only = true;
		return MS_BLOCK_INVALID;
	}

	msb_mark_block_used(msb, pba);
	return pba;
}