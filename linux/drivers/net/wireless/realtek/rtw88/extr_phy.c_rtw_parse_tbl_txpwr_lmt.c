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
struct rtw_txpwr_lmt_cfg_pair {int /*<<< orphan*/  txpwr_lmt; int /*<<< orphan*/  ch; int /*<<< orphan*/  rs; int /*<<< orphan*/  bw; int /*<<< orphan*/  band; int /*<<< orphan*/  regd; } ;
struct rtw_table {int size; struct rtw_txpwr_lmt_cfg_pair* data; } ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw_phy_set_tx_power_limit (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_xref_txpwr_lmt (struct rtw_dev*) ; 

void rtw_parse_tbl_txpwr_lmt(struct rtw_dev *rtwdev,
			     const struct rtw_table *tbl)
{
	const struct rtw_txpwr_lmt_cfg_pair *p = tbl->data;
	const struct rtw_txpwr_lmt_cfg_pair *end = p + tbl->size;

	for (; p < end; p++) {
		rtw_phy_set_tx_power_limit(rtwdev, p->regd, p->band,
					   p->bw, p->rs, p->ch, p->txpwr_lmt);
	}

	rtw_xref_txpwr_lmt(rtwdev);
}