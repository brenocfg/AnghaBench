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
typedef  int uint32_t ;
struct dcn20_vmid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*) ; 
 int /*<<< orphan*/  PAGE_TABLE_BASE_ADDR_LO32 ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VM_CONTEXT0_PAGE_DIRECTORY_ENTRY_LO32 ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void dcn20_wait_for_vmid_ready(struct dcn20_vmid *vmid)
{
	/* According the hardware spec, we need to poll for the lowest
	 * bit of PAGE_TABLE_BASE_ADDR_LO32 = 1 any time a GPUVM
	 * context is updated. We can't use REG_WAIT here since we
	 * don't have a seperate field to wait on.
	 *
	 * TODO: Confirm timeout / poll interval with hardware team
	 */

	int max_times = 10000;
	int delay_us  = 5;
	int i;

	for (i = 0; i < max_times; ++i) {
		uint32_t entry_lo32;

		REG_GET(PAGE_TABLE_BASE_ADDR_LO32,
			VM_CONTEXT0_PAGE_DIRECTORY_ENTRY_LO32,
			&entry_lo32);

		if (entry_lo32 & 0x1)
			return;

		udelay(delay_us);
	}

	/* VM setup timed out */
	DC_LOG_WARNING("Timeout while waiting for GPUVM context update\n");
	ASSERT(0);
}