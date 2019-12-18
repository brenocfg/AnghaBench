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
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  GTFIFODBG ; 
 int __raw_uncore_read32 (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_uncore_write32 (struct intel_uncore*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
gen6_check_for_fifo_debug(struct intel_uncore *uncore)
{
	u32 fifodbg;

	fifodbg = __raw_uncore_read32(uncore, GTFIFODBG);

	if (unlikely(fifodbg)) {
		DRM_DEBUG_DRIVER("GTFIFODBG = 0x08%x\n", fifodbg);
		__raw_uncore_write32(uncore, GTFIFODBG, fifodbg);
	}

	return fifodbg;
}