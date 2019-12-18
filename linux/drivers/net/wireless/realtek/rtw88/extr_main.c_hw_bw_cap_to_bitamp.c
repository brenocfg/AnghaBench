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

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
#define  EFUSE_HW_CAP_IGNORE 130 
#define  EFUSE_HW_CAP_SUPP_BW40 129 
#define  EFUSE_HW_CAP_SUPP_BW80 128 
 int /*<<< orphan*/  RTW_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  RTW_CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  RTW_CHANNEL_WIDTH_80 ; 

__attribute__((used)) static u8 hw_bw_cap_to_bitamp(u8 bw_cap)
{
	u8 bw = 0;

	switch (bw_cap) {
	case EFUSE_HW_CAP_IGNORE:
	case EFUSE_HW_CAP_SUPP_BW80:
		bw |= BIT(RTW_CHANNEL_WIDTH_80);
		/* fall through */
	case EFUSE_HW_CAP_SUPP_BW40:
		bw |= BIT(RTW_CHANNEL_WIDTH_40);
		/* fall through */
	default:
		bw |= BIT(RTW_CHANNEL_WIDTH_20);
		break;
	}

	return bw;
}