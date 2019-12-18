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
struct dram_dimm_info {int ranks; scalar_t__ width; } ;

/* Variables and functions */

__attribute__((used)) static int intel_dimm_num_devices(const struct dram_dimm_info *dimm)
{
	return dimm->ranks * 64 / (dimm->width ?: 1);
}