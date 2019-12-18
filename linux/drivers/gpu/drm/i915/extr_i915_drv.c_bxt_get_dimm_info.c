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
struct dram_dimm_info {int size; int /*<<< orphan*/  ranks; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_get_dimm_ranks (int /*<<< orphan*/ ) ; 
 int bxt_get_dimm_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxt_get_dimm_width (int /*<<< orphan*/ ) ; 
 int intel_dimm_num_devices (struct dram_dimm_info*) ; 

__attribute__((used)) static void bxt_get_dimm_info(struct dram_dimm_info *dimm,
			      u32 val)
{
	dimm->width = bxt_get_dimm_width(val);
	dimm->ranks = bxt_get_dimm_ranks(val);

	/*
	 * Size in register is Gb per DRAM device. Convert to total
	 * GB to match the way we report this for non-LP platforms.
	 */
	dimm->size = bxt_get_dimm_size(val) * intel_dimm_num_devices(dimm) / 8;
}