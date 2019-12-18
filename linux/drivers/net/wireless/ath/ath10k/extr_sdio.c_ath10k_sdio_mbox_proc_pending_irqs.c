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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SDIO ; 
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_HOST_INT_STATUS_COUNTER_MASK ; 
 int /*<<< orphan*/  MBOX_HOST_INT_STATUS_CPU_MASK ; 
 int /*<<< orphan*/  MBOX_HOST_INT_STATUS_ERROR_MASK ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,...) ; 
 int ath10k_sdio_mbox_proc_counter_intr (struct ath10k*) ; 
 int ath10k_sdio_mbox_proc_cpu_intr (struct ath10k*) ; 
 int ath10k_sdio_mbox_proc_err_intr (struct ath10k*) ; 
 int ath10k_sdio_mbox_read_int_status (struct ath10k*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int ath10k_sdio_mbox_rxmsg_pending_handler (struct ath10k*,scalar_t__,int*) ; 

__attribute__((used)) static int ath10k_sdio_mbox_proc_pending_irqs(struct ath10k *ar,
					      bool *done)
{
	u8 host_int_status;
	u32 lookahead;
	int ret;

	/* NOTE: HIF implementation guarantees that the context of this
	 * call allows us to perform SYNCHRONOUS I/O, that is we can block,
	 * sleep or call any API that can block or switch thread/task
	 * contexts. This is a fully schedulable context.
	 */

	ret = ath10k_sdio_mbox_read_int_status(ar,
					       &host_int_status,
					       &lookahead);
	if (ret) {
		*done = true;
		goto out;
	}

	if (!host_int_status && !lookahead) {
		ret = 0;
		*done = true;
		goto out;
	}

	if (lookahead) {
		ath10k_dbg(ar, ATH10K_DBG_SDIO,
			   "sdio pending mailbox msg lookahead 0x%08x\n",
			   lookahead);

		ret = ath10k_sdio_mbox_rxmsg_pending_handler(ar,
							     lookahead,
							     done);
		if (ret)
			goto out;
	}

	/* now, handle the rest of the interrupts */
	ath10k_dbg(ar, ATH10K_DBG_SDIO,
		   "sdio host_int_status 0x%x\n", host_int_status);

	if (FIELD_GET(MBOX_HOST_INT_STATUS_CPU_MASK, host_int_status)) {
		/* CPU Interrupt */
		ret = ath10k_sdio_mbox_proc_cpu_intr(ar);
		if (ret)
			goto out;
	}

	if (FIELD_GET(MBOX_HOST_INT_STATUS_ERROR_MASK, host_int_status)) {
		/* Error Interrupt */
		ret = ath10k_sdio_mbox_proc_err_intr(ar);
		if (ret)
			goto out;
	}

	if (FIELD_GET(MBOX_HOST_INT_STATUS_COUNTER_MASK, host_int_status))
		/* Counter Interrupt */
		ret = ath10k_sdio_mbox_proc_counter_intr(ar);

	ret = 0;

out:
	/* An optimization to bypass reading the IRQ status registers
	 * unecessarily which can re-wake the target, if upper layers
	 * determine that we are in a low-throughput mode, we can rely on
	 * taking another interrupt rather than re-checking the status
	 * registers which can re-wake the target.
	 *
	 * NOTE : for host interfaces that makes use of detecting pending
	 * mbox messages at hif can not use this optimization due to
	 * possible side effects, SPI requires the host to drain all
	 * messages from the mailbox before exiting the ISR routine.
	 */

	ath10k_dbg(ar, ATH10K_DBG_SDIO,
		   "sdio pending irqs done %d status %d",
		   *done, ret);

	return ret;
}