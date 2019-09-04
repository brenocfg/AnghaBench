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
struct sdma_engine {int imask; int /*<<< orphan*/  this_idx; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int /*<<< orphan*/ * int_counter; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CCE_INT_CLEAR ; 
 scalar_t__ CCE_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int IS_SDMA_START ; 
 int /*<<< orphan*/  dd_dev_info_ratelimited (struct hfi1_devdata*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int read_csr (struct hfi1_devdata*,scalar_t__) ; 
 int /*<<< orphan*/  sdma_engine_interrupt (struct sdma_engine*,int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int) ; 

__attribute__((used)) static irqreturn_t sdma_interrupt(int irq, void *data)
{
	struct sdma_engine *sde = data;
	struct hfi1_devdata *dd = sde->dd;
	u64 status;

#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__FILE__), __LINE__, __func__);
	sdma_dumpstate(sde);
#endif

	this_cpu_inc(*dd->int_counter);

	/* This read_csr is really bad in the hot path */
	status = read_csr(dd,
			  CCE_INT_STATUS + (8 * (IS_SDMA_START / 64)))
			  & sde->imask;
	if (likely(status)) {
		/* clear the interrupt(s) */
		write_csr(dd,
			  CCE_INT_CLEAR + (8 * (IS_SDMA_START / 64)),
			  status);

		/* handle the interrupt(s) */
		sdma_engine_interrupt(sde, status);
	} else {
		dd_dev_info_ratelimited(dd, "SDMA engine %u interrupt, but no status bits set\n",
					sde->this_idx);
	}
	return IRQ_HANDLED;
}