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
#define  DP_LINK_BW_1_62 131 
#define  DP_LINK_BW_2_7 130 
#define  DP_LINK_BW_5_4 129 
#define  DP_LINK_BW_8_1 128 
 int /*<<< orphan*/  WARN (int,char*,int) ; 

int drm_dp_bw_code_to_link_rate(u8 link_bw)
{
	switch (link_bw) {
	default:
		WARN(1, "unknown DP link BW code %x, using 162000\n", link_bw);
	case DP_LINK_BW_1_62:
		return 162000;
	case DP_LINK_BW_2_7:
		return 270000;
	case DP_LINK_BW_5_4:
		return 540000;
	case DP_LINK_BW_8_1:
		return 810000;
	}
}