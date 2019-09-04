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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  interrupt_clear_down (struct hfi1_devdata*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_eng_err ; 

__attribute__((used)) static void is_sdma_eng_err_int(struct hfi1_devdata *dd, unsigned int source)
{
#ifdef CONFIG_SDMA_VERBOSITY
	struct sdma_engine *sde = &dd->per_sdma[source];

	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__FILE__), __LINE__, __func__);
	dd_dev_err(dd, "CONFIG SDMA(%u) source: %u\n", sde->this_idx,
		   source);
	sdma_dumpstate(sde);
#endif
	interrupt_clear_down(dd, source, &sdma_eng_err);
}