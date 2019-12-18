#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ath10k_sdio_irq_data {int /*<<< orphan*/  mtx; TYPE_2__* irq_en_reg; TYPE_1__* irq_proc_reg; } ;
struct ath10k_sdio {struct ath10k_sdio_irq_data irq_data; } ;
struct ath10k {int dummy; } ;
struct TYPE_4__ {int cntr_int_status_en; } ;
struct TYPE_3__ {int counter_int_status; } ;

/* Variables and functions */
 int ATH10K_SDIO_TARGET_DEBUG_INTR_MASK ; 
 int ath10k_sdio_mbox_proc_dbg_intr (struct ath10k*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_sdio_mbox_proc_counter_intr(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	u8 counter_int_status;
	int ret;

	mutex_lock(&irq_data->mtx);
	counter_int_status = irq_data->irq_proc_reg->counter_int_status &
			     irq_data->irq_en_reg->cntr_int_status_en;

	/* NOTE: other modules like GMBOX may use the counter interrupt for
	 * credit flow control on other counters, we only need to check for
	 * the debug assertion counter interrupt.
	 */
	if (counter_int_status & ATH10K_SDIO_TARGET_DEBUG_INTR_MASK)
		ret = ath10k_sdio_mbox_proc_dbg_intr(ar);
	else
		ret = 0;

	mutex_unlock(&irq_data->mtx);

	return ret;
}