#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ngene {scalar_t__ icounts; int cmd_done; int* ngenetohost; int EventQueueWriteIndex; scalar_t__ EventQueueReadIndex; int EventQueueOverflowCount; int EventQueueOverflowFlag; TYPE_6__* channel; int /*<<< orphan*/  event_tasklet; TYPE_2__* EventBuffer; TYPE_2__* EventQueue; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  cmd_wq; scalar_t__* CmdDoneByte; scalar_t__ BootFirmware; TYPE_1__* pci_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_12__ {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  demux_tasklet; TYPE_5__* nextBuffer; } ;
struct TYPE_9__ {int Flags; } ;
struct TYPE_10__ {TYPE_3__ SR; } ;
struct TYPE_11__ {TYPE_4__ ngeneBuffer; } ;
struct TYPE_8__ {int EventStatus; } ;
struct TYPE_7__ {struct device dev; } ;

/* Variables and functions */
 int EVENT_QUEUE_SIZE ; 
 int /*<<< orphan*/  FORCE_NMI ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ MAX_STREAM ; 
 int /*<<< orphan*/  NGENE_INT_COUNTS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ ngreadl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngwritel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t irq_handler(int irq, void *dev_id)
{
	struct ngene *dev = (struct ngene *)dev_id;
	struct device *pdev = &dev->pci_dev->dev;
	u32 icounts = 0;
	irqreturn_t rc = IRQ_NONE;
	u32 i = MAX_STREAM;
	u8 *tmpCmdDoneByte;

	if (dev->BootFirmware) {
		icounts = ngreadl(NGENE_INT_COUNTS);
		if (icounts != dev->icounts) {
			ngwritel(0, FORCE_NMI);
			dev->cmd_done = 1;
			wake_up(&dev->cmd_wq);
			dev->icounts = icounts;
			rc = IRQ_HANDLED;
		}
		return rc;
	}

	ngwritel(0, FORCE_NMI);

	spin_lock(&dev->cmd_lock);
	tmpCmdDoneByte = dev->CmdDoneByte;
	if (tmpCmdDoneByte &&
	    (*tmpCmdDoneByte ||
	    (dev->ngenetohost[0] == 1 && dev->ngenetohost[1] != 0))) {
		dev->CmdDoneByte = NULL;
		dev->cmd_done = 1;
		wake_up(&dev->cmd_wq);
		rc = IRQ_HANDLED;
	}
	spin_unlock(&dev->cmd_lock);

	if (dev->EventBuffer->EventStatus & 0x80) {
		u8 nextWriteIndex =
			(dev->EventQueueWriteIndex + 1) &
			(EVENT_QUEUE_SIZE - 1);
		if (nextWriteIndex != dev->EventQueueReadIndex) {
			dev->EventQueue[dev->EventQueueWriteIndex] =
				*(dev->EventBuffer);
			dev->EventQueueWriteIndex = nextWriteIndex;
		} else {
			dev_err(pdev, "event overflow\n");
			dev->EventQueueOverflowCount += 1;
			dev->EventQueueOverflowFlag = 1;
		}
		dev->EventBuffer->EventStatus &= ~0x80;
		tasklet_schedule(&dev->event_tasklet);
		rc = IRQ_HANDLED;
	}

	while (i > 0) {
		i--;
		spin_lock(&dev->channel[i].state_lock);
		/* if (dev->channel[i].State>=KSSTATE_RUN) { */
		if (dev->channel[i].nextBuffer) {
			if ((dev->channel[i].nextBuffer->
			     ngeneBuffer.SR.Flags & 0xC0) == 0x80) {
				dev->channel[i].nextBuffer->
					ngeneBuffer.SR.Flags |= 0x40;
				tasklet_schedule(
					&dev->channel[i].demux_tasklet);
				rc = IRQ_HANDLED;
			}
		}
		spin_unlock(&dev->channel[i].state_lock);
	}

	/* Request might have been processed by a previous call. */
	return IRQ_HANDLED;
}