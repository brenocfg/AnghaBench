#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct rtw_phy_cond {int branch; scalar_t__ neg; scalar_t__ pos; int /*<<< orphan*/  member_0; } ;
union phy_table_tile {TYPE_1__ cfg; struct rtw_phy_cond cond; } ;
struct rtw_table {int size; int /*<<< orphan*/  (* do_cfg ) (struct rtw_dev*,struct rtw_table const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;union phy_table_tile* data; } ;
struct rtw_dev {int dummy; } ;
struct phy_cfg_pair {int dummy; } ;

/* Variables and functions */
#define  BRANCH_ELIF 131 
#define  BRANCH_ELSE 130 
#define  BRANCH_ENDIF 129 
#define  BRANCH_IF 128 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ check_positive (struct rtw_dev*,struct rtw_phy_cond) ; 
 int /*<<< orphan*/  stub1 (struct rtw_dev*,struct rtw_table const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_parse_tbl_phy_cond(struct rtw_dev *rtwdev, const struct rtw_table *tbl)
{
	const union phy_table_tile *p = tbl->data;
	const union phy_table_tile *end = p + tbl->size / 2;
	struct rtw_phy_cond pos_cond = {0};
	bool is_matched = true, is_skipped = false;

	BUILD_BUG_ON(sizeof(union phy_table_tile) != sizeof(struct phy_cfg_pair));

	for (; p < end; p++) {
		if (p->cond.pos) {
			switch (p->cond.branch) {
			case BRANCH_ENDIF:
				is_matched = true;
				is_skipped = false;
				break;
			case BRANCH_ELSE:
				is_matched = is_skipped ? false : true;
				break;
			case BRANCH_IF:
			case BRANCH_ELIF:
			default:
				pos_cond = p->cond;
				break;
			}
		} else if (p->cond.neg) {
			if (!is_skipped) {
				if (check_positive(rtwdev, pos_cond)) {
					is_matched = true;
					is_skipped = true;
				} else {
					is_matched = false;
					is_skipped = false;
				}
			} else {
				is_matched = false;
			}
		} else if (is_matched) {
			(*tbl->do_cfg)(rtwdev, tbl, p->cfg.addr, p->cfg.data);
		}
	}
}