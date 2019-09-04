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
struct hfi1_devdata {unsigned int num_sdma; int /*<<< orphan*/ * per_sdma; } ;

/* Variables and functions */
 unsigned int TXE_NUM_SDMA_ENGINES ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sdma_engine_interrupt (int /*<<< orphan*/ *,unsigned long long) ; 

__attribute__((used)) static void is_sdma_eng_int(struct hfi1_devdata *dd, unsigned int source)
{
	/* what interrupt */
	unsigned int what  = source / TXE_NUM_SDMA_ENGINES;
	/* which engine */
	unsigned int which = source % TXE_NUM_SDMA_ENGINES;

#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", which,
		   slashstrip(__FILE__), __LINE__, __func__);
	sdma_dumpstate(&dd->per_sdma[which]);
#endif

	if (likely(what < 3 && which < dd->num_sdma)) {
		sdma_engine_interrupt(&dd->per_sdma[which], 1ull << source);
	} else {
		/* should not happen */
		dd_dev_err(dd, "Invalid SDMA interrupt 0x%x\n", source);
	}
}