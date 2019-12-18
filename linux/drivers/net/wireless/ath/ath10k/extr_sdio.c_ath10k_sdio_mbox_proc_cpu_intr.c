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
struct ath10k_sdio_irq_data {int /*<<< orphan*/  mtx; TYPE_2__* irq_proc_reg; TYPE_1__* irq_en_reg; } ;
struct ath10k_sdio {struct ath10k_sdio_irq_data irq_data; } ;
struct ath10k {int /*<<< orphan*/  restart_work; int /*<<< orphan*/  workqueue; } ;
struct TYPE_4__ {int cpu_int_status; } ;
struct TYPE_3__ {int cpu_int_status_en; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MBOX_CPU_INT_STATUS_ADDRESS ; 
 int MBOX_CPU_STATUS_ENABLE_ASSERT_MASK ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*) ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int ath10k_sdio_writesb32 (struct ath10k*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_sdio_mbox_proc_cpu_intr(struct ath10k *ar)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct ath10k_sdio_irq_data *irq_data = &ar_sdio->irq_data;
	u8 cpu_int_status;
	int ret;

	mutex_lock(&irq_data->mtx);
	cpu_int_status = irq_data->irq_proc_reg->cpu_int_status &
			 irq_data->irq_en_reg->cpu_int_status_en;
	if (!cpu_int_status) {
		ath10k_warn(ar, "CPU interrupt status is zero\n");
		ret = -EIO;
		goto out;
	}

	/* Clear the interrupt */
	irq_data->irq_proc_reg->cpu_int_status &= ~cpu_int_status;

	/* Set up the register transfer buffer to hit the register 4 times,
	 * this is done to make the access 4-byte aligned to mitigate issues
	 * with host bus interconnects that restrict bus transfer lengths to
	 * be a multiple of 4-bytes.
	 *
	 * Set W1C value to clear the interrupt, this hits the register first.
	 */
	ret = ath10k_sdio_writesb32(ar, MBOX_CPU_INT_STATUS_ADDRESS,
				    cpu_int_status);
	if (ret) {
		ath10k_warn(ar, "unable to write to cpu interrupt status address: %d\n",
			    ret);
		goto out;
	}

out:
	mutex_unlock(&irq_data->mtx);
	if (cpu_int_status & MBOX_CPU_STATUS_ENABLE_ASSERT_MASK) {
		ath10k_err(ar, "firmware crashed!\n");
		queue_work(ar->workqueue, &ar->restart_work);
	}
	return ret;
}