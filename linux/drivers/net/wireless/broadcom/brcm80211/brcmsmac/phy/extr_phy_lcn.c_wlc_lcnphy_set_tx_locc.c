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
typedef  int /*<<< orphan*/  u16 ;
struct phytbl_info {int tbl_width; int tbl_len; int tbl_offset; int /*<<< orphan*/ * tbl_ptr; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_IQLOCAL ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

void wlc_lcnphy_set_tx_locc(struct brcms_phy *pi, u16 didq)
{
	struct phytbl_info tab;

	tab.tbl_id = LCNPHY_TBL_ID_IQLOCAL;
	tab.tbl_width = 16;
	tab.tbl_ptr = &didq;
	tab.tbl_len = 1;
	tab.tbl_offset = 85;
	wlc_lcnphy_write_table(pi, &tab);
}