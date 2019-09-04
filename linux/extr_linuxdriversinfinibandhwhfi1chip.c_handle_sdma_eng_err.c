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
typedef  unsigned long long u64 ;
struct sdma_engine {int /*<<< orphan*/  err_cnt; } ;
struct hfi1_devdata {int /*<<< orphan*/ * sw_send_dma_eng_err_status_cnt; struct sdma_engine* per_sdma; } ;

/* Variables and functions */
 int NUM_SEND_DMA_ENG_ERR_STATUS_COUNTERS ; 
 int /*<<< orphan*/  incr_cntr64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdma_engine_error (struct sdma_engine*,unsigned long long) ; 

__attribute__((used)) static void handle_sdma_eng_err(struct hfi1_devdata *dd,
				unsigned int source, u64 status)
{
	struct sdma_engine *sde;
	int i = 0;

	sde = &dd->per_sdma[source];
#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n", sde->this_idx,
		   slashstrip(__FILE__), __LINE__, __func__);
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) source: %u status 0x%llx\n",
		   sde->this_idx, source, (unsigned long long)status);
#endif
	sde->err_cnt++;
	sdma_engine_error(sde, status);

	/*
	* Update the counters for the corresponding status bits.
	* Note that these particular counters are aggregated over
	* all 16 DMA engines.
	*/
	for (i = 0; i < NUM_SEND_DMA_ENG_ERR_STATUS_COUNTERS; i++) {
		if (status & (1ull << i))
			incr_cntr64(&dd->sw_send_dma_eng_err_status_cnt[i]);
	}
}