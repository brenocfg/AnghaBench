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
typedef  int u32 ;
struct zone_entry {scalar_t__ unused_blk_cnt; size_t set_index; size_t get_index; int* free_table; } ;
struct xd_info {int zone_cnt; struct zone_entry* zone; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */
 int BLK_NOT_FOUND ; 
 size_t XD_FREE_TABLE_CNT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_zone (struct zone_entry*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 

__attribute__((used)) static u32 xd_get_unused_block(struct rtsx_chip *chip, int zone_no)
{
	struct xd_info *xd_card = &chip->xd_card;
	struct zone_entry *zone;
	u32 phy_blk;

	if (zone_no >= xd_card->zone_cnt) {
		dev_dbg(rtsx_dev(chip), "Get unused block from invalid zone (zone_no = %d, zone_cnt = %d)\n",
			zone_no, xd_card->zone_cnt);
		return BLK_NOT_FOUND;
	}
	zone = &xd_card->zone[zone_no];

	if ((zone->unused_blk_cnt == 0) ||
	    (zone->set_index == zone->get_index)) {
		free_zone(zone);
		dev_dbg(rtsx_dev(chip), "Get unused block fail, no unused block available\n");
		return BLK_NOT_FOUND;
	}
	if ((zone->get_index >= XD_FREE_TABLE_CNT) || (zone->get_index < 0)) {
		free_zone(zone);
		dev_dbg(rtsx_dev(chip), "Get unused block fail, invalid get_index\n");
		return BLK_NOT_FOUND;
	}

	dev_dbg(rtsx_dev(chip), "Get unused block from index %d\n",
		zone->get_index);

	phy_blk = zone->free_table[zone->get_index];
	zone->free_table[zone->get_index++] = 0xFFFF;
	if (zone->get_index >= XD_FREE_TABLE_CNT)
		zone->get_index = 0;
	zone->unused_blk_cnt--;

	phy_blk += ((u32)(zone_no) << 10);
	return phy_blk;
}