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
struct mei_txe_hw {int aliveness; int /*<<< orphan*/  slots; int /*<<< orphan*/  intr_cause; int /*<<< orphan*/  wait_aliveness_resp; int /*<<< orphan*/  readiness; } ;
struct mei_device {int recvd_hw_ready; scalar_t__ dev_state; int hbuf_is_ready; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  pg_event; int /*<<< orphan*/  wait_hw_ready; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  HHISR_REG ; 
 int /*<<< orphan*/  HISR_REG ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MEI_DEV_POWER_DOWN ; 
 scalar_t__ MEI_DEV_RESETTING ; 
 int /*<<< orphan*/  MEI_PG_EVENT_RECEIVED ; 
 int /*<<< orphan*/  SEC_IPC_HOST_INT_STATUS_REG ; 
 int /*<<< orphan*/  TXE_HBUF_DEPTH ; 
 int /*<<< orphan*/  TXE_INTR_ALIVENESS_BIT ; 
 int /*<<< orphan*/  TXE_INTR_IN_READY_BIT ; 
 int /*<<< orphan*/  TXE_INTR_OUT_DB_BIT ; 
 int /*<<< orphan*/  TXE_INTR_READINESS_BIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_count_full_read_slots (struct mei_device*) ; 
 int /*<<< orphan*/  mei_enable_interrupts (struct mei_device*) ; 
 void* mei_hbuf_is_ready (struct mei_device*) ; 
 int /*<<< orphan*/  mei_irq_compl_handler (struct mei_device*,struct list_head*) ; 
 int mei_irq_read_handler (struct mei_device*,struct list_head*,int /*<<< orphan*/ *) ; 
 int mei_irq_write_handler (struct mei_device*,struct list_head*) ; 
 int mei_txe_aliveness_get (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_br_reg_read (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_check_and_ack_intrs (struct mei_device*,int) ; 
 int /*<<< orphan*/  mei_txe_pending_interrupts (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_readiness_get (struct mei_device*) ; 
 scalar_t__ mei_txe_readiness_is_sec_rdy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_sec_reg_read_silent (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_dev_msi_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t mei_txe_irq_thread_handler(int irq, void *dev_id)
{
	struct mei_device *dev = (struct mei_device *) dev_id;
	struct mei_txe_hw *hw = to_txe_hw(dev);
	struct list_head cmpl_list;
	s32 slots;
	int rets = 0;

	dev_dbg(dev->dev, "irq thread: Interrupt Registers HHISR|HISR|SEC=%02X|%04X|%02X\n",
		mei_txe_br_reg_read(hw, HHISR_REG),
		mei_txe_br_reg_read(hw, HISR_REG),
		mei_txe_sec_reg_read_silent(hw, SEC_IPC_HOST_INT_STATUS_REG));


	/* initialize our complete list */
	mutex_lock(&dev->device_lock);
	INIT_LIST_HEAD(&cmpl_list);

	if (pci_dev_msi_enabled(to_pci_dev(dev->dev)))
		mei_txe_check_and_ack_intrs(dev, true);

	/* show irq events */
	mei_txe_pending_interrupts(dev);

	hw->aliveness = mei_txe_aliveness_get(dev);
	hw->readiness = mei_txe_readiness_get(dev);

	/* Readiness:
	 * Detection of TXE driver going through reset
	 * or TXE driver resetting the HECI interface.
	 */
	if (test_and_clear_bit(TXE_INTR_READINESS_BIT, &hw->intr_cause)) {
		dev_dbg(dev->dev, "Readiness Interrupt was received...\n");

		/* Check if SeC is going through reset */
		if (mei_txe_readiness_is_sec_rdy(hw->readiness)) {
			dev_dbg(dev->dev, "we need to start the dev.\n");
			dev->recvd_hw_ready = true;
		} else {
			dev->recvd_hw_ready = false;
			if (dev->dev_state != MEI_DEV_RESETTING) {

				dev_warn(dev->dev, "FW not ready: resetting.\n");
				schedule_work(&dev->reset_work);
				goto end;

			}
		}
		wake_up(&dev->wait_hw_ready);
	}

	/************************************************************/
	/* Check interrupt cause:
	 * Aliveness: Detection of SeC acknowledge of host request that
	 * it remain alive or host cancellation of that request.
	 */

	if (test_and_clear_bit(TXE_INTR_ALIVENESS_BIT, &hw->intr_cause)) {
		/* Clear the interrupt cause */
		dev_dbg(dev->dev,
			"Aliveness Interrupt: Status: %d\n", hw->aliveness);
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		if (waitqueue_active(&hw->wait_aliveness_resp))
			wake_up(&hw->wait_aliveness_resp);
	}


	/* Output Doorbell:
	 * Detection of SeC having sent output to host
	 */
	slots = mei_count_full_read_slots(dev);
	if (test_and_clear_bit(TXE_INTR_OUT_DB_BIT, &hw->intr_cause)) {
		/* Read from TXE */
		rets = mei_irq_read_handler(dev, &cmpl_list, &slots);
		if (rets &&
		    (dev->dev_state != MEI_DEV_RESETTING &&
		     dev->dev_state != MEI_DEV_POWER_DOWN)) {
			dev_err(dev->dev,
				"mei_irq_read_handler ret = %d.\n", rets);

			schedule_work(&dev->reset_work);
			goto end;
		}
	}
	/* Input Ready: Detection if host can write to SeC */
	if (test_and_clear_bit(TXE_INTR_IN_READY_BIT, &hw->intr_cause)) {
		dev->hbuf_is_ready = true;
		hw->slots = TXE_HBUF_DEPTH;
	}

	if (hw->aliveness && dev->hbuf_is_ready) {
		/* get the real register value */
		dev->hbuf_is_ready = mei_hbuf_is_ready(dev);
		rets = mei_irq_write_handler(dev, &cmpl_list);
		if (rets && rets != -EMSGSIZE)
			dev_err(dev->dev, "mei_irq_write_handler ret = %d.\n",
				rets);
		dev->hbuf_is_ready = mei_hbuf_is_ready(dev);
	}

	mei_irq_compl_handler(dev, &cmpl_list);

end:
	dev_dbg(dev->dev, "interrupt thread end ret = %d\n", rets);

	mutex_unlock(&dev->device_lock);

	mei_enable_interrupts(dev);
	return IRQ_HANDLED;
}