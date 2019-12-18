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
struct mei_device {scalar_t__ dev_state; int recvd_hw_ready; scalar_t__ pg_event; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  dev; void* hbuf_is_ready; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  wait_hw_ready; } ;
struct list_head {int dummy; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MEI_DEV_POWER_DOWN ; 
 scalar_t__ MEI_DEV_RESETTING ; 
 scalar_t__ MEI_PG_EVENT_RECEIVED ; 
 scalar_t__ MEI_PG_EVENT_WAIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  me_intr_clear (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  me_intr_src (int /*<<< orphan*/ ) ; 
 scalar_t__ mei_count_full_read_slots (struct mei_device*) ; 
 void* mei_hbuf_is_ready (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hcsr_read (struct mei_device*) ; 
 int /*<<< orphan*/  mei_hcsr_set_hig (struct mei_device*) ; 
 int /*<<< orphan*/  mei_host_is_ready (struct mei_device*) ; 
 scalar_t__ mei_hw_is_ready (struct mei_device*) ; 
 int /*<<< orphan*/  mei_irq_compl_handler (struct mei_device*,struct list_head*) ; 
 int mei_irq_read_handler (struct mei_device*,struct list_head*,scalar_t__*) ; 
 int mei_irq_write_handler (struct mei_device*,struct list_head*) ; 
 scalar_t__ mei_me_hw_is_resetting (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_intr_enable (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_pg_intr (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t mei_me_irq_thread_handler(int irq, void *dev_id)
{
	struct mei_device *dev = (struct mei_device *) dev_id;
	struct list_head cmpl_list;
	s32 slots;
	u32 hcsr;
	int rets = 0;

	dev_dbg(dev->dev, "function called after ISR to handle the interrupt processing.\n");
	/* initialize our complete list */
	mutex_lock(&dev->device_lock);

	hcsr = mei_hcsr_read(dev);
	me_intr_clear(dev, hcsr);

	INIT_LIST_HEAD(&cmpl_list);

	/* check if ME wants a reset */
	if (!mei_hw_is_ready(dev) && dev->dev_state != MEI_DEV_RESETTING) {
		dev_warn(dev->dev, "FW not ready: resetting.\n");
		schedule_work(&dev->reset_work);
		goto end;
	}

	if (mei_me_hw_is_resetting(dev))
		mei_hcsr_set_hig(dev);

	mei_me_pg_intr(dev, me_intr_src(hcsr));

	/*  check if we need to start the dev */
	if (!mei_host_is_ready(dev)) {
		if (mei_hw_is_ready(dev)) {
			dev_dbg(dev->dev, "we need to start the dev.\n");
			dev->recvd_hw_ready = true;
			wake_up(&dev->wait_hw_ready);
		} else {
			dev_dbg(dev->dev, "Spurious Interrupt\n");
		}
		goto end;
	}
	/* check slots available for reading */
	slots = mei_count_full_read_slots(dev);
	while (slots > 0) {
		dev_dbg(dev->dev, "slots to read = %08x\n", slots);
		rets = mei_irq_read_handler(dev, &cmpl_list, &slots);
		/* There is a race between ME write and interrupt delivery:
		 * Not all data is always available immediately after the
		 * interrupt, so try to read again on the next interrupt.
		 */
		if (rets == -ENODATA)
			break;

		if (rets &&
		    (dev->dev_state != MEI_DEV_RESETTING &&
		     dev->dev_state != MEI_DEV_POWER_DOWN)) {
			dev_err(dev->dev, "mei_irq_read_handler ret = %d.\n",
						rets);
			schedule_work(&dev->reset_work);
			goto end;
		}
	}

	dev->hbuf_is_ready = mei_hbuf_is_ready(dev);

	/*
	 * During PG handshake only allowed write is the replay to the
	 * PG exit message, so block calling write function
	 * if the pg event is in PG handshake
	 */
	if (dev->pg_event != MEI_PG_EVENT_WAIT &&
	    dev->pg_event != MEI_PG_EVENT_RECEIVED) {
		rets = mei_irq_write_handler(dev, &cmpl_list);
		dev->hbuf_is_ready = mei_hbuf_is_ready(dev);
	}

	mei_irq_compl_handler(dev, &cmpl_list);

end:
	dev_dbg(dev->dev, "interrupt thread end ret = %d\n", rets);
	mei_me_intr_enable(dev);
	mutex_unlock(&dev->device_lock);
	return IRQ_HANDLED;
}