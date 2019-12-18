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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ CCE_ERR_CLEAR ; 
 scalar_t__ CCE_INT_CLEAR ; 
 int CCE_NUM_INT_CSRS ; 
 scalar_t__ DCC_ERR_FLG_CLR ; 
 scalar_t__ DC_DC8051_ERR_CLR ; 
 scalar_t__ DC_LCB_ERR_CLR ; 
 scalar_t__ MISC_ERR_CLEAR ; 
 scalar_t__ RCV_ERR_CLEAR ; 
 int /*<<< orphan*/  SEND_CTXT_ERR_CLEAR ; 
 int /*<<< orphan*/  SEND_DMA_ENG_ERR_CLEAR ; 
 scalar_t__ SEND_DMA_ERR_CLEAR ; 
 scalar_t__ SEND_EGRESS_ERR_CLEAR ; 
 scalar_t__ SEND_ERR_CLEAR ; 
 scalar_t__ SEND_PIO_ERR_CLEAR ; 
 int chip_sdma_engines (struct hfi1_devdata*) ; 
 int chip_send_contexts (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kctxt_csr (struct hfi1_devdata*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void clear_all_interrupts(struct hfi1_devdata *dd)
{
	int i;

	for (i = 0; i < CCE_NUM_INT_CSRS; i++)
		write_csr(dd, CCE_INT_CLEAR + (8 * i), ~(u64)0);

	write_csr(dd, CCE_ERR_CLEAR, ~(u64)0);
	write_csr(dd, MISC_ERR_CLEAR, ~(u64)0);
	write_csr(dd, RCV_ERR_CLEAR, ~(u64)0);
	write_csr(dd, SEND_ERR_CLEAR, ~(u64)0);
	write_csr(dd, SEND_PIO_ERR_CLEAR, ~(u64)0);
	write_csr(dd, SEND_DMA_ERR_CLEAR, ~(u64)0);
	write_csr(dd, SEND_EGRESS_ERR_CLEAR, ~(u64)0);
	for (i = 0; i < chip_send_contexts(dd); i++)
		write_kctxt_csr(dd, i, SEND_CTXT_ERR_CLEAR, ~(u64)0);
	for (i = 0; i < chip_sdma_engines(dd); i++)
		write_kctxt_csr(dd, i, SEND_DMA_ENG_ERR_CLEAR, ~(u64)0);

	write_csr(dd, DCC_ERR_FLG_CLR, ~(u64)0);
	write_csr(dd, DC_LCB_ERR_CLR, ~(u64)0);
	write_csr(dd, DC_DC8051_ERR_CLR, ~(u64)0);
}