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

/* Variables and functions */
 unsigned long ST0_KPS ; 
 unsigned long ST0_UPS ; 
 int /*<<< orphan*/  build_tlb_refill_handler () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  probe_tlb (unsigned int) ; 
 unsigned int read_c0_config () ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 
 int /*<<< orphan*/  write_c0_wired (int /*<<< orphan*/ ) ; 

void tlb_init(void)
{
	unsigned int config = read_c0_config();
	unsigned long status;

	probe_tlb(config);

	status = read_c0_status();
	status &= ~(ST0_UPS | ST0_KPS);
#ifdef CONFIG_PAGE_SIZE_4KB
	status |= (TFP_PAGESIZE_4K << 32) | (TFP_PAGESIZE_4K << 36);
#elif defined(CONFIG_PAGE_SIZE_8KB)
	status |= (TFP_PAGESIZE_8K << 32) | (TFP_PAGESIZE_8K << 36);
#elif defined(CONFIG_PAGE_SIZE_16KB)
	status |= (TFP_PAGESIZE_16K << 32) | (TFP_PAGESIZE_16K << 36);
#elif defined(CONFIG_PAGE_SIZE_64KB)
	status |= (TFP_PAGESIZE_64K << 32) | (TFP_PAGESIZE_64K << 36);
#endif
	write_c0_status(status);

	write_c0_wired(0);

	local_flush_tlb_all();

	build_tlb_refill_handler();
}