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
struct sdma_engine {scalar_t__* head_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENG_ERR_CLEAR ; 
 int /*<<< orphan*/  ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_MASK ; 
 int /*<<< orphan*/  ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_SHIFT ; 
 int SD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdma_setlengen (struct sdma_engine*) ; 
 int /*<<< orphan*/  sdma_update_tail (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sde_csr (struct sdma_engine*,int,int) ; 

__attribute__((used)) static void sdma_hw_start_up(struct sdma_engine *sde)
{
	u64 reg;

#ifdef CONFIG_SDMA_VERBOSITY
	dd_dev_err(sde->dd, "CONFIG SDMA(%u) %s:%d %s()\n",
		   sde->this_idx, slashstrip(__FILE__), __LINE__, __func__);
#endif

	sdma_setlengen(sde);
	sdma_update_tail(sde, 0); /* Set SendDmaTail */
	*sde->head_dma = 0;

	reg = SD(ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_MASK) <<
	      SD(ENG_ERR_CLEAR_SDMA_HEADER_REQUEST_FIFO_UNC_ERR_SHIFT);
	write_sde_csr(sde, SD(ENG_ERR_CLEAR), reg);
}