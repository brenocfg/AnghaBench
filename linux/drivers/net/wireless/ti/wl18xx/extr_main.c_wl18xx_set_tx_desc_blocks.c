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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  total_mem_blocks; } ;
struct wl1271_tx_hw_descr {TYPE_1__ wl18xx_mem; } ;
struct wl1271 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
wl18xx_set_tx_desc_blocks(struct wl1271 *wl, struct wl1271_tx_hw_descr *desc,
			  u32 blks, u32 spare_blks)
{
	desc->wl18xx_mem.total_mem_blocks = blks;
}