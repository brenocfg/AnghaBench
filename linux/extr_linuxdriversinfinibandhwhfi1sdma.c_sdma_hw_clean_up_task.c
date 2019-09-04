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
typedef  int u64 ;
struct sdma_engine {int dummy; } ;

/* Variables and functions */
 int SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  STATUS_ENG_CLEANED_UP_SMASK ; 
 int read_sde_csr (struct sdma_engine*,int) ; 
 int /*<<< orphan*/  sdma_event_e25_hw_clean_up_done ; 
 int /*<<< orphan*/  sdma_process_event (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sdma_hw_clean_up_task(unsigned long opaque)
{
	struct sdma_engine *sde = (struct sdma_engine *)opaque;
	u64 statuscsr;

	while (1) {
#ifdef CONFIG_SDMA_VERBOSITY
		dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
			   sde->this_idx, slashstrip(__FILE__), __LINE__,
			__func__);
#endif
		statuscsr = read_sde_csr(sde, SD(STATUS));
		statuscsr &= SD(STATUS_ENG_CLEANED_UP_SMASK);
		if (statuscsr)
			break;
		udelay(10);
	}

	sdma_process_event(sde, sdma_event_e25_hw_clean_up_done);
}