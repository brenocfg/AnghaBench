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
struct msb_data {int read_only; int /*<<< orphan*/ * free_block_count; int /*<<< orphan*/  used_blocks_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 int msb_get_zone_from_pba (int) ; 
 scalar_t__ msb_validate_used_block_bitmap (struct msb_data*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msb_mark_block_unused(struct msb_data *msb, int pba)
{
	int zone = msb_get_zone_from_pba(pba);

	if (!test_bit(pba, msb->used_blocks_bitmap)) {
		pr_err("BUG: attempt to mark already unused pba %d as unused" , pba);
		msb->read_only = true;
		return;
	}

	if (msb_validate_used_block_bitmap(msb))
		return;

	/* No races because all IO is single threaded */
	__clear_bit(pba, msb->used_blocks_bitmap);
	msb->free_block_count[zone]++;
}