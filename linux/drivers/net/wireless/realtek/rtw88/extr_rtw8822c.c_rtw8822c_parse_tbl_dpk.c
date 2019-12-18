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
struct rtw_table {int size; struct dpk_cfg_pair* data; } ;
struct rtw_dev {int dummy; } ;
struct dpk_cfg_pair {int /*<<< orphan*/  data; int /*<<< orphan*/  bitmask; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw8822c_parse_tbl_dpk(struct rtw_dev *rtwdev,
			    const struct rtw_table *tbl)
{
	const struct dpk_cfg_pair *p = tbl->data;
	const struct dpk_cfg_pair *end = p + tbl->size / 3;

	BUILD_BUG_ON(sizeof(struct dpk_cfg_pair) != sizeof(u32) * 3);

	for (; p < end; p++)
		rtw_write32_mask(rtwdev, p->addr, p->bitmask, p->data);
}