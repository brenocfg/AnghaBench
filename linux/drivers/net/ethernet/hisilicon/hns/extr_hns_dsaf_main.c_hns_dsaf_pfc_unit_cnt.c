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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_device {int dummy; } ;
typedef  enum dsaf_port_rate_mode { ____Placeholder_dsaf_port_rate_mode } dsaf_port_rate_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_PFC_UNINT_CNT_M ; 
 int /*<<< orphan*/  DSAF_PFC_UNINT_CNT_S ; 
 scalar_t__ DSAF_PFC_UNIT_CNT_0_REG ; 
#define  DSAF_PORT_RATE_1000 130 
#define  DSAF_PORT_RATE_10000 129 
#define  DSAF_PORT_RATE_2500 128 
 int /*<<< orphan*/  HNS_DSAF_PFC_UNIT_CNT_FOR_GE_1000 ; 
 int /*<<< orphan*/  HNS_DSAF_PFC_UNIT_CNT_FOR_XGE ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_pfc_unit_cnt(struct dsaf_device *dsaf_dev, int  mac_id,
				  enum dsaf_port_rate_mode rate)
{
	u32 unit_cnt;

	switch (rate) {
	case DSAF_PORT_RATE_10000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_XGE;
		break;
	case DSAF_PORT_RATE_1000:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_GE_1000;
		break;
	case DSAF_PORT_RATE_2500:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_GE_1000;
		break;
	default:
		unit_cnt = HNS_DSAF_PFC_UNIT_CNT_FOR_XGE;
	}

	dsaf_set_dev_field(dsaf_dev,
			   (DSAF_PFC_UNIT_CNT_0_REG + 0x4 * (u64)mac_id),
			   DSAF_PFC_UNINT_CNT_M, DSAF_PFC_UNINT_CNT_S,
			   unit_cnt);
}