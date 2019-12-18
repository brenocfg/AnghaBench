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
typedef  size_t u16 ;
struct zone_entry {size_t* l2p_table; } ;
struct xd_info {struct zone_entry* zone; } ;
struct rtsx_chip {struct xd_info xd_card; } ;

/* Variables and functions */

__attribute__((used)) static void xd_set_l2p_tbl(struct rtsx_chip *chip,
			   int zone_no, u16 log_off, u16 phy_off)
{
	struct xd_info *xd_card = &chip->xd_card;
	struct zone_entry *zone;

	zone = &xd_card->zone[zone_no];
	zone->l2p_table[log_off] = phy_off;
}