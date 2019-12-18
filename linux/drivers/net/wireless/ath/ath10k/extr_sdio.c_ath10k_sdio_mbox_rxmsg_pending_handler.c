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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k_sdio {int n_rx_pkts; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ATH10K_SDIO_MAX_RX_MSGS ; 
 int ECANCELED ; 
 unsigned long SDIO_MBOX_PROCESSING_TIMEOUT_HZ ; 
 int ath10k_sdio_mbox_rx_alloc (struct ath10k*,int /*<<< orphan*/ *,int) ; 
 int ath10k_sdio_mbox_rx_fetch (struct ath10k*) ; 
 int ath10k_sdio_mbox_rx_process_packets (struct ath10k*,int /*<<< orphan*/ *,int*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ath10k_sdio_mbox_rxmsg_pending_handler(struct ath10k *ar,
						  u32 msg_lookahead, bool *done)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	u32 lookaheads[ATH10K_SDIO_MAX_RX_MSGS];
	int n_lookaheads = 1;
	unsigned long timeout;
	int ret;

	*done = true;

	/* Copy the lookahead obtained from the HTC register table into our
	 * temp array as a start value.
	 */
	lookaheads[0] = msg_lookahead;

	timeout = jiffies + SDIO_MBOX_PROCESSING_TIMEOUT_HZ;
	do {
		/* Try to allocate as many HTC RX packets indicated by
		 * n_lookaheads.
		 */
		ret = ath10k_sdio_mbox_rx_alloc(ar, lookaheads,
						n_lookaheads);
		if (ret)
			break;

		if (ar_sdio->n_rx_pkts >= 2)
			/* A recv bundle was detected, force IRQ status
			 * re-check again.
			 */
			*done = false;

		ret = ath10k_sdio_mbox_rx_fetch(ar);

		/* Process fetched packets. This will potentially update
		 * n_lookaheads depending on if the packets contain lookahead
		 * reports.
		 */
		n_lookaheads = 0;
		ret = ath10k_sdio_mbox_rx_process_packets(ar,
							  lookaheads,
							  &n_lookaheads);

		if (!n_lookaheads || ret)
			break;

		/* For SYNCH processing, if we get here, we are running
		 * through the loop again due to updated lookaheads. Set
		 * flag that we should re-check IRQ status registers again
		 * before leaving IRQ processing, this can net better
		 * performance in high throughput situations.
		 */
		*done = false;
	} while (time_before(jiffies, timeout));

	if (ret && (ret != -ECANCELED))
		ath10k_warn(ar, "failed to get pending recv messages: %d\n",
			    ret);

	return ret;
}