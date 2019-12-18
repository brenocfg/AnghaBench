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
struct intel_uncore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_DBG ; 
 int FPGA_DBG_RM_NOCLAIM ; 
 int __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_uncore_write32 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static bool
fpga_check_for_unclaimed_mmio(struct intel_uncore *uncore)
{
	u32 dbg;

	dbg = __raw_uncore_read32(uncore, FPGA_DBG);
	if (likely(!(dbg & FPGA_DBG_RM_NOCLAIM)))
		return false;

	__raw_uncore_write32(uncore, FPGA_DBG, FPGA_DBG_RM_NOCLAIM);

	return true;
}