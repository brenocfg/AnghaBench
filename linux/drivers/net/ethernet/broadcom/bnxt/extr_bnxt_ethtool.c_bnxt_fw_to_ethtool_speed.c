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
typedef  int u16 ;

/* Variables and functions */
#define  BNXT_LINK_SPEED_100GB 136 
#define  BNXT_LINK_SPEED_100MB 135 
#define  BNXT_LINK_SPEED_10GB 134 
#define  BNXT_LINK_SPEED_1GB 133 
#define  BNXT_LINK_SPEED_20GB 132 
#define  BNXT_LINK_SPEED_25GB 131 
#define  BNXT_LINK_SPEED_2_5GB 130 
#define  BNXT_LINK_SPEED_40GB 129 
#define  BNXT_LINK_SPEED_50GB 128 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_100000 ; 
 int /*<<< orphan*/  SPEED_20000 ; 
 int /*<<< orphan*/  SPEED_2500 ; 
 int /*<<< orphan*/  SPEED_25000 ; 
 int /*<<< orphan*/  SPEED_40000 ; 
 int /*<<< orphan*/  SPEED_50000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 

u32 bnxt_fw_to_ethtool_speed(u16 fw_link_speed)
{
	switch (fw_link_speed) {
	case BNXT_LINK_SPEED_100MB:
		return SPEED_100;
	case BNXT_LINK_SPEED_1GB:
		return SPEED_1000;
	case BNXT_LINK_SPEED_2_5GB:
		return SPEED_2500;
	case BNXT_LINK_SPEED_10GB:
		return SPEED_10000;
	case BNXT_LINK_SPEED_20GB:
		return SPEED_20000;
	case BNXT_LINK_SPEED_25GB:
		return SPEED_25000;
	case BNXT_LINK_SPEED_40GB:
		return SPEED_40000;
	case BNXT_LINK_SPEED_50GB:
		return SPEED_50000;
	case BNXT_LINK_SPEED_100GB:
		return SPEED_100000;
	default:
		return SPEED_UNKNOWN;
	}
}