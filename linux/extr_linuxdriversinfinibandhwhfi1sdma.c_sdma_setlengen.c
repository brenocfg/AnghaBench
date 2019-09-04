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
struct sdma_engine {int descq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEN_GEN ; 
 int /*<<< orphan*/  LEN_GEN_GENERATION_SHIFT ; 
 int /*<<< orphan*/  LEN_GEN_LENGTH_SHIFT ; 
 unsigned long long SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sde_csr (struct sdma_engine*,unsigned long long,int) ; 

__attribute__((used)) static void sdma_setlengen(struct sdma_engine *sde)
{
#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__FILE__), __LINE__, __func__);
#endif

	/*
	 * Set SendDmaLenGen and clear-then-set the MSB of the generation
	 * count to enable generation checking and load the internal
	 * generation counter.
	 */
	write_sde_csr(sde, SD(LEN_GEN),
		      (sde->descq_cnt / 64) << SD(LEN_GEN_LENGTH_SHIFT));
	write_sde_csr(sde, SD(LEN_GEN),
		      ((sde->descq_cnt / 64) << SD(LEN_GEN_LENGTH_SHIFT)) |
		      (4ULL << SD(LEN_GEN_GENERATION_SHIFT)));
}