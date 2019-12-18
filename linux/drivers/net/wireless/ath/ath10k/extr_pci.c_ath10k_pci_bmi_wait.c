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
struct bmi_xfer {scalar_t__ rx_done; scalar_t__ wait_for_resp; scalar_t__ tx_done; } ;
struct ath10k_ce_pipe {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BMI ; 
 unsigned long BMI_COMMUNICATION_TIMEOUT_HZ ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  ath10k_pci_bmi_recv_data (struct ath10k_ce_pipe*) ; 
 int /*<<< orphan*/  ath10k_pci_bmi_send_done (struct ath10k_ce_pipe*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_before_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int ath10k_pci_bmi_wait(struct ath10k *ar,
			       struct ath10k_ce_pipe *tx_pipe,
			       struct ath10k_ce_pipe *rx_pipe,
			       struct bmi_xfer *xfer)
{
	unsigned long timeout = jiffies + BMI_COMMUNICATION_TIMEOUT_HZ;
	unsigned long started = jiffies;
	unsigned long dur;
	int ret;

	while (time_before_eq(jiffies, timeout)) {
		ath10k_pci_bmi_send_done(tx_pipe);
		ath10k_pci_bmi_recv_data(rx_pipe);

		if (xfer->tx_done && (xfer->rx_done == xfer->wait_for_resp)) {
			ret = 0;
			goto out;
		}

		schedule();
	}

	ret = -ETIMEDOUT;

out:
	dur = jiffies - started;
	if (dur > HZ)
		ath10k_dbg(ar, ATH10K_DBG_BMI,
			   "bmi cmd took %lu jiffies hz %d ret %d\n",
			   dur, HZ, ret);
	return ret;
}