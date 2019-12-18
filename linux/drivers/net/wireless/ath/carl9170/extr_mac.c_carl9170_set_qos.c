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
struct ar9170 {TYPE_1__* edcf; } ;
struct TYPE_2__ {int cw_min; int cw_max; int aifs; int txop; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_REG_AC0_CW ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC1_AC0_TXOP ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC1_CW ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC2_AC1_AC0_AIFS ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC2_CW ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC3_AC2_TXOP ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC3_CW ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC4_AC3_AC2_AIFS ; 
 int /*<<< orphan*/  AR9170_MAC_REG_AC4_CW ; 
 int /*<<< orphan*/  carl9170_regwrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

int carl9170_set_qos(struct ar9170 *ar)
{
	carl9170_regwrite_begin(ar);

	carl9170_regwrite(AR9170_MAC_REG_AC0_CW, ar->edcf[0].cw_min |
			  (ar->edcf[0].cw_max << 16));
	carl9170_regwrite(AR9170_MAC_REG_AC1_CW, ar->edcf[1].cw_min |
			  (ar->edcf[1].cw_max << 16));
	carl9170_regwrite(AR9170_MAC_REG_AC2_CW, ar->edcf[2].cw_min |
			  (ar->edcf[2].cw_max << 16));
	carl9170_regwrite(AR9170_MAC_REG_AC3_CW, ar->edcf[3].cw_min |
			  (ar->edcf[3].cw_max << 16));
	carl9170_regwrite(AR9170_MAC_REG_AC4_CW, ar->edcf[4].cw_min |
			  (ar->edcf[4].cw_max << 16));

	carl9170_regwrite(AR9170_MAC_REG_AC2_AC1_AC0_AIFS,
			  ((ar->edcf[0].aifs * 9 + 10)) |
			  ((ar->edcf[1].aifs * 9 + 10) << 12) |
			  ((ar->edcf[2].aifs * 9 + 10) << 24));
	carl9170_regwrite(AR9170_MAC_REG_AC4_AC3_AC2_AIFS,
			  ((ar->edcf[2].aifs * 9 + 10) >> 8) |
			  ((ar->edcf[3].aifs * 9 + 10) << 4) |
			  ((ar->edcf[4].aifs * 9 + 10) << 16));

	carl9170_regwrite(AR9170_MAC_REG_AC1_AC0_TXOP,
			  ar->edcf[0].txop | ar->edcf[1].txop << 16);
	carl9170_regwrite(AR9170_MAC_REG_AC3_AC2_TXOP,
			  ar->edcf[2].txop | ar->edcf[3].txop << 16 |
			  ar->edcf[4].txop << 24);

	carl9170_regwrite_finish();

	return carl9170_regwrite_result();
}