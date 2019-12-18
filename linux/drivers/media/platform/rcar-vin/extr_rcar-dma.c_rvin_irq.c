#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  field; } ;
struct rvin_dev {scalar_t__ state; int sequence; int /*<<< orphan*/  qlock; TYPE_2__** queue_buf; TYPE_1__ format; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_5__ {int sequence; TYPE_3__ vb2_buf; int /*<<< orphan*/  field; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 scalar_t__ RUNNING ; 
 scalar_t__ STARTING ; 
 scalar_t__ STOPPED ; 
 scalar_t__ STOPPING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int VNMS_FBS_MASK ; 
 int VNMS_FBS_SHIFT ; 
 int /*<<< orphan*/  VNMS_REG ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  rvin_ack_interrupt (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_fill_hw_slot (struct rvin_dev*,int) ; 
 int rvin_get_interrupt_status (struct rvin_dev*) ; 
 int rvin_read (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vb2_buffer_done (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,...) ; 

__attribute__((used)) static irqreturn_t rvin_irq(int irq, void *data)
{
	struct rvin_dev *vin = data;
	u32 int_status, vnms;
	int slot;
	unsigned int handled = 0;
	unsigned long flags;

	spin_lock_irqsave(&vin->qlock, flags);

	int_status = rvin_get_interrupt_status(vin);
	if (!int_status)
		goto done;

	rvin_ack_interrupt(vin);
	handled = 1;

	/* Nothing to do if capture status is 'STOPPED' */
	if (vin->state == STOPPED) {
		vin_dbg(vin, "IRQ while state stopped\n");
		goto done;
	}

	/* Nothing to do if capture status is 'STOPPING' */
	if (vin->state == STOPPING) {
		vin_dbg(vin, "IRQ while state stopping\n");
		goto done;
	}

	/* Prepare for capture and update state */
	vnms = rvin_read(vin, VNMS_REG);
	slot = (vnms & VNMS_FBS_MASK) >> VNMS_FBS_SHIFT;

	/*
	 * To hand buffers back in a known order to userspace start
	 * to capture first from slot 0.
	 */
	if (vin->state == STARTING) {
		if (slot != 0) {
			vin_dbg(vin, "Starting sync slot: %d\n", slot);
			goto done;
		}

		vin_dbg(vin, "Capture start synced!\n");
		vin->state = RUNNING;
	}

	/* Capture frame */
	if (vin->queue_buf[slot]) {
		vin->queue_buf[slot]->field = vin->format.field;
		vin->queue_buf[slot]->sequence = vin->sequence;
		vin->queue_buf[slot]->vb2_buf.timestamp = ktime_get_ns();
		vb2_buffer_done(&vin->queue_buf[slot]->vb2_buf,
				VB2_BUF_STATE_DONE);
		vin->queue_buf[slot] = NULL;
	} else {
		/* Scratch buffer was used, dropping frame. */
		vin_dbg(vin, "Dropping frame %u\n", vin->sequence);
	}

	vin->sequence++;

	/* Prepare for next frame */
	rvin_fill_hw_slot(vin, slot);
done:
	spin_unlock_irqrestore(&vin->qlock, flags);

	return IRQ_RETVAL(handled);
}