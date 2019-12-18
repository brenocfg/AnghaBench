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
typedef  scalar_t__ u32 ;
struct ath10k_sdio_irq_proc_regs {int host_int_status; int rx_lookahead_valid; int /*<<< orphan*/ * rx_lookahead; } ;
struct ath10k_sdio_irq_enable_regs {int int_status_en; } ;
struct ath10k_sdio_irq_data {int /*<<< orphan*/  mtx; struct ath10k_sdio_irq_enable_regs* irq_en_reg; struct ath10k_sdio_irq_proc_regs* irq_proc_reg; } ;
struct ath10k_sdio {struct ath10k_sdio_irq_data irq_data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ATH10K_HTC_MAILBOX ; 
 int /*<<< orphan*/  ATH10K_HTC_MAILBOX_MASK ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MBOX_HOST_INT_STATUS_ADDRESS ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int ath10k_sdio_read (struct ath10k*,int /*<<< orphan*/ ,struct ath10k_sdio_irq_proc_regs*,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_sdio_mbox_read_int_status(struct ath10k *ar,
					    u8 *host_int_status,
					    u32 *lookahead)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	struct ath10k_sdio_irq_proc_regs *irq_proc_reg = irq_data->irq_proc_reg;
	struct ath10k_sdio_irq_enable_regs *irq_en_reg = irq_data->irq_en_reg;
	u8 htc_mbox = FIELD_PREP(ATH10K_HTC_MAILBOX_MASK, 1);
	int ret;

	mutex_lock(&irq_data->mtx);

	*lookahead = 0;
	*host_int_status = 0;

	/* int_status_en is supposed to be non zero, otherwise interrupts
	 * shouldn't be enabled. There is however a short time frame during
	 * initialization between the irq register and int_status_en init
	 * where this can happen.
	 * We silently ignore this condition.
	 */
	if (!irq_en_reg->int_status_en) {
		ret = 0;
		goto out;
	}

	/* Read the first sizeof(struct ath10k_irq_proc_registers)
	 * bytes of the HTC register table. This
	 * will yield us the value of different int status
	 * registers and the lookahead registers.
	 */
	ret = ath10k_sdio_read(ar, MBOX_HOST_INT_STATUS_ADDRESS,
			       irq_proc_reg, sizeof(*irq_proc_reg));
	if (ret)
		goto out;

	/* Update only those registers that are enabled */
	*host_int_status = irq_proc_reg->host_int_status &
			   irq_en_reg->int_status_en;

	/* Look at mbox status */
	if (!(*host_int_status & htc_mbox)) {
		*lookahead = 0;
		ret = 0;
		goto out;
	}

	/* Mask out pending mbox value, we use look ahead as
	 * the real flag for mbox processing.
	 */
	*host_int_status &= ~htc_mbox;
	if (irq_proc_reg->rx_lookahead_valid & htc_mbox) {
		*lookahead = le32_to_cpu(
			irq_proc_reg->rx_lookahead[ATH10K_HTC_MAILBOX]);
		if (!*lookahead)
			ath10k_warn(ar, "sdio mbox lookahead is zero\n");
	}

out:
	mutex_unlock(&irq_data->mtx);
	return ret;
}