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
struct iwl_fw_runtime {int dummy; } ;
struct iwl_fw_ini_region_cfg {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 iwl_dump_ini_mon_dram_ranges(struct iwl_fw_runtime *fwrt,
					struct iwl_fw_ini_region_cfg *reg)
{
	return 1;
}