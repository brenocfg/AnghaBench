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
struct zone_entry {int* l2p_table; } ;
struct ms_info {struct zone_entry* segment; } ;
struct rtsx_chip {struct ms_info ms_card; } ;

/* Variables and functions */

__attribute__((used)) static u16 ms_get_l2p_tbl(struct rtsx_chip *chip, int seg_no, u16 log_off)
{
	struct ms_info *ms_card = &chip->ms_card;
	struct zone_entry *segment;

	if (!ms_card->segment)
		return 0xFFFF;

	segment = &ms_card->segment[seg_no];

	if (segment->l2p_table)
		return segment->l2p_table[log_off];

	return 0xFFFF;
}