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
struct iwl_fw_runtime {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_of_ranges; } ;
struct iwl_fw_ini_region_cfg {TYPE_1__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 iwl_dump_ini_mem_ranges(struct iwl_fw_runtime *fwrt,
				   struct iwl_fw_ini_region_cfg *reg)
{
	return le32_to_cpu(reg->internal.num_of_ranges);
}