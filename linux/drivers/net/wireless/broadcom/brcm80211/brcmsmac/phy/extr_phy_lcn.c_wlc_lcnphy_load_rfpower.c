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
typedef  int u8 ;
typedef  int u32 ;
struct phytbl_info {int tbl_width; int tbl_len; int* tbl_ptr; scalar_t__ tbl_offset; int /*<<< orphan*/  tbl_id; } ;
struct brcms_phy {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 int /*<<< orphan*/  LCNPHY_TBL_ID_TXPWRCTL ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_GAIN_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_IQ_OFFSET ; 
 scalar_t__ LCNPHY_TX_PWR_CTRL_PWR_OFFSET ; 
 int /*<<< orphan*/  qm_log10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ qm_shr16 (scalar_t__,scalar_t__) ; 
 scalar_t__ qm_sub16 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wlc_lcnphy_read_table (struct brcms_phy*,struct phytbl_info*) ; 
 int /*<<< orphan*/  wlc_lcnphy_write_table (struct brcms_phy*,struct phytbl_info*) ; 

__attribute__((used)) static void wlc_lcnphy_load_rfpower(struct brcms_phy *pi)
{
	struct phytbl_info tab;
	u32 val, bbmult, rfgain;
	u8 index;
	u8 scale_factor = 1;
	s16 temp, temp1, temp2, qQ, qQ1, qQ2, shift;

	tab.tbl_id = LCNPHY_TBL_ID_TXPWRCTL;
	tab.tbl_width = 32;
	tab.tbl_len = 1;

	for (index = 0; index < 128; index++) {
		tab.tbl_ptr = &bbmult;
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_IQ_OFFSET + index;
		wlc_lcnphy_read_table(pi, &tab);
		bbmult = bbmult >> 20;

		tab.tbl_ptr = &rfgain;
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_GAIN_OFFSET + index;
		wlc_lcnphy_read_table(pi, &tab);

		qm_log10((s32) (bbmult), 0, &temp1, &qQ1);
		qm_log10((s32) (1 << 6), 0, &temp2, &qQ2);

		if (qQ1 < qQ2) {
			temp2 = qm_shr16(temp2, qQ2 - qQ1);
			qQ = qQ1;
		} else {
			temp1 = qm_shr16(temp1, qQ1 - qQ2);
			qQ = qQ2;
		}
		temp = qm_sub16(temp1, temp2);

		if (qQ >= 4)
			shift = qQ - 4;
		else
			shift = 4 - qQ;

		val = (((index << shift) + (5 * temp) +
			(1 << (scale_factor + shift - 3))) >> (scale_factor +
							       shift - 2));

		tab.tbl_ptr = &val;
		tab.tbl_offset = LCNPHY_TX_PWR_CTRL_PWR_OFFSET + index;
		wlc_lcnphy_write_table(pi, &tab);
	}
}