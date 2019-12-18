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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ath6kl_irq_proc_registers {int host_int_status; int rx_lkahd_valid; int counter_int_status; int /*<<< orphan*/ * rx_lkahd; } ;
struct ath6kl_device {struct ath6kl_irq_proc_registers irq_proc_reg; int /*<<< orphan*/  ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HIF ; 
 int ATH6KL_TARGET_DEBUG_INTR_MASK ; 
 int ATH6KL_TIME_QUANTUM ; 
 int ETIME ; 
 int /*<<< orphan*/  HIF_RD_SYNC_BYTE_INC ; 
 int /*<<< orphan*/  HOST_INT_STATUS_ADDRESS ; 
 int HTC_MAILBOX ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  ath6kl_hif_proc_dbg_intr (struct ath6kl_device*) ; 
 int hif_read_write_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

int ath6kl_hif_poll_mboxmsg_rx(struct ath6kl_device *dev, u32 *lk_ahd,
			      int timeout)
{
	struct ath6kl_irq_proc_registers *rg;
	int status = 0, i;
	u8 htc_mbox = 1 << HTC_MAILBOX;

	for (i = timeout / ATH6KL_TIME_QUANTUM; i > 0; i--) {
		/* this is the standard HIF way, load the reg table */
		status = hif_read_write_sync(dev->ar, HOST_INT_STATUS_ADDRESS,
					     (u8 *) &dev->irq_proc_reg,
					     sizeof(dev->irq_proc_reg),
					     HIF_RD_SYNC_BYTE_INC);

		if (status) {
			ath6kl_err("failed to read reg table\n");
			return status;
		}

		/* check for MBOX data and valid lookahead */
		if (dev->irq_proc_reg.host_int_status & htc_mbox) {
			if (dev->irq_proc_reg.rx_lkahd_valid &
			    htc_mbox) {
				/*
				 * Mailbox has a message and the look ahead
				 * is valid.
				 */
				rg = &dev->irq_proc_reg;
				*lk_ahd =
					le32_to_cpu(rg->rx_lkahd[HTC_MAILBOX]);
				break;
			}
		}

		/* delay a little  */
		mdelay(ATH6KL_TIME_QUANTUM);
		ath6kl_dbg(ATH6KL_DBG_HIF, "hif retry mbox poll try %d\n", i);
	}

	if (i == 0) {
		ath6kl_err("timeout waiting for recv message\n");
		status = -ETIME;
		/* check if the target asserted */
		if (dev->irq_proc_reg.counter_int_status &
		    ATH6KL_TARGET_DEBUG_INTR_MASK)
			/*
			 * Target failure handler will be called in case of
			 * an assert.
			 */
			ath6kl_hif_proc_dbg_intr(dev);
	}

	return status;
}