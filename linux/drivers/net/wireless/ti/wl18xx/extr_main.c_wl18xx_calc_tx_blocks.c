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
struct wl1271 {int dummy; } ;

/* Variables and functions */
 int WL18XX_TX_HW_BLOCK_SIZE ; 

__attribute__((used)) static u32 wl18xx_calc_tx_blocks(struct wl1271 *wl, u32 len, u32 spare_blks)
{
	u32 blk_size = WL18XX_TX_HW_BLOCK_SIZE;
	return (len + blk_size - 1) / blk_size + spare_blks;
}