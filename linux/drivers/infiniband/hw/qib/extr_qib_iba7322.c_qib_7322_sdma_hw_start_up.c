#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int current_op; } ;
struct qib_pportdata {TYPE_1__ sdma_state; scalar_t__* sdma_head_dma; } ;

/* Variables and functions */
 int QIB_SDMA_SENDCTRL_OP_CLEANUP ; 
 int /*<<< orphan*/  QIB_SENDCTRL_FLUSH ; 
 int /*<<< orphan*/  qib_7322_sdma_sendctrl (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  qib_sdma_7322_setlengen (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_sdma_update_7322_tail (struct qib_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendctrl_7322_mod (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qib_7322_sdma_hw_start_up(struct qib_pportdata *ppd)
{
	/*
	 * Drain all FIFOs.
	 * The hardware doesn't require this but we do it so that verbs
	 * and user applications don't wait for link active to send stale
	 * data.
	 */
	sendctrl_7322_mod(ppd, QIB_SENDCTRL_FLUSH);

	qib_sdma_7322_setlengen(ppd);
	qib_sdma_update_7322_tail(ppd, 0); /* Set SendDmaTail */
	ppd->sdma_head_dma[0] = 0;
	qib_7322_sdma_sendctrl(ppd,
		ppd->sdma_state.current_op | QIB_SDMA_SENDCTRL_OP_CLEANUP);
}