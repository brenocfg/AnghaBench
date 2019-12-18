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
struct rtw_table {int size; struct phy_pg_cfg_pair* data; } ;
struct rtw_dev {int dummy; } ;
struct phy_pg_cfg_pair {int addr; int /*<<< orphan*/  data; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  tx_num; int /*<<< orphan*/  rf_path; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtw_phy_store_tx_power_by_rate (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_parse_tbl_bb_pg(struct rtw_dev *rtwdev, const struct rtw_table *tbl)
{
	const struct phy_pg_cfg_pair *p = tbl->data;
	const struct phy_pg_cfg_pair *end = p + tbl->size / 6;

	BUILD_BUG_ON(sizeof(struct phy_pg_cfg_pair) != sizeof(u32) * 6);

	for (; p < end; p++) {
		if (p->addr == 0xfe || p->addr == 0xffe) {
			msleep(50);
			continue;
		}
		rtw_phy_store_tx_power_by_rate(rtwdev, p->band, p->rf_path,
					       p->tx_num, p->addr, p->bitmask,
					       p->data);
	}
}