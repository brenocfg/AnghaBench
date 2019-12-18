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
typedef  scalar_t__ u16 ;
struct zone_entry {scalar_t__ set_index; int /*<<< orphan*/  unused_blk_cnt; scalar_t__* free_table; } ;
struct ms_info {struct zone_entry* segment; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */
 scalar_t__ MS_FREE_TABLE_CNT ; 

__attribute__((used)) static void ms_set_unused_block(struct rtsx_chip *chip, u16 phy_blk)
{
	struct ms_info *ms_card = &chip->ms_card;
	struct zone_entry *segment;
	int seg_no;

	seg_no = (int)phy_blk >> 9;
	segment = &ms_card->segment[seg_no];

	segment->free_table[segment->set_index++] = phy_blk;
	if (segment->set_index >= MS_FREE_TABLE_CNT)
		segment->set_index = 0;

	segment->unused_blk_cnt++;
}