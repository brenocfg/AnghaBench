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
struct mbus_dram_target_info {int dummy; } ;

/* Variables and functions */
 struct mbus_dram_target_info const mvebu_mbus_dram_info_nooverlap ; 

const struct mbus_dram_target_info *mv_mbus_dram_info_nooverlap(void)
{
	return &mvebu_mbus_dram_info_nooverlap;
}