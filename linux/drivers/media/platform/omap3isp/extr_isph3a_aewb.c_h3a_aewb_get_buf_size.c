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
typedef  int u32 ;
struct omap3isp_h3a_aewb_config {int ver_win_count; int hor_win_count; } ;

/* Variables and functions */
 int AEWB_PACKET_SIZE ; 

__attribute__((used)) static u32 h3a_aewb_get_buf_size(struct omap3isp_h3a_aewb_config *conf)
{
	/* Number of configured windows + extra row for black data */
	u32 win_count = (conf->ver_win_count + 1) * conf->hor_win_count;

	/*
	 * Unsaturated block counts for each 8 windows.
	 * 1 extra for the last (win_count % 8) windows if win_count is not
	 * divisible by 8.
	 */
	win_count += (win_count + 7) / 8;

	return win_count * AEWB_PACKET_SIZE;
}