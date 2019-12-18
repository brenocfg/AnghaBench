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
struct v4l2_device {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  hdl; } ;
struct TYPE_4__ {struct cx18** sliced_mpeg_data; } ;
struct cx18 {int /*<<< orphan*/  card_name; TYPE_2__ av_state; TYPE_1__ vbi; TYPE_3__* pci_dev; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  in_work_queue; int /*<<< orphan*/  tot_capturing; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX18_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  CX18_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX18_MEM_SIZE ; 
 int CX18_VBI_FRAMES ; 
 int IRQ_APU_TO_EPU ; 
 int IRQ_APU_TO_EPU_ACK ; 
 int IRQ_CPU_TO_EPU ; 
 int IRQ_CPU_TO_EPU_ACK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx18_cancel_in_work_orders (struct cx18*) ; 
 int /*<<< orphan*/  cx18_cancel_out_work_orders (struct cx18*) ; 
 int /*<<< orphan*/  cx18_halt_firmware (struct cx18*) ; 
 int /*<<< orphan*/  cx18_iounmap (struct cx18*) ; 
 int /*<<< orphan*/  cx18_stop_all_captures (struct cx18*) ; 
 int /*<<< orphan*/  cx18_streams_cleanup (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_sw1_irq_disable (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_sw2_irq_disable (struct cx18*,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_cx18_i2c (struct cx18*) ; 
 int /*<<< orphan*/  flush_request_modules (struct cx18*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kfree (struct cx18*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_3__*) ; 
 struct v4l2_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx18* to_cx18 (struct v4l2_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (struct v4l2_device*) ; 

__attribute__((used)) static void cx18_remove(struct pci_dev *pci_dev)
{
	struct v4l2_device *v4l2_dev = pci_get_drvdata(pci_dev);
	struct cx18 *cx = to_cx18(v4l2_dev);
	int i;

	CX18_DEBUG_INFO("Removing Card\n");

	flush_request_modules(cx);

	/* Stop all captures */
	CX18_DEBUG_INFO("Stopping all streams\n");
	if (atomic_read(&cx->tot_capturing) > 0)
		cx18_stop_all_captures(cx);

	/* Stop interrupts that cause incoming work to be queued */
	cx18_sw1_irq_disable(cx, IRQ_CPU_TO_EPU | IRQ_APU_TO_EPU);

	/* Incoming work can cause outgoing work, so clean up incoming first */
	cx18_cancel_in_work_orders(cx);
	cx18_cancel_out_work_orders(cx);

	/* Stop ack interrupts that may have been needed for work to finish */
	cx18_sw2_irq_disable(cx, IRQ_CPU_TO_EPU_ACK | IRQ_APU_TO_EPU_ACK);

	cx18_halt_firmware(cx);

	destroy_workqueue(cx->in_work_queue);

	cx18_streams_cleanup(cx, 1);

	exit_cx18_i2c(cx);

	free_irq(cx->pci_dev->irq, (void *)cx);

	cx18_iounmap(cx);

	release_mem_region(cx->base_addr, CX18_MEM_SIZE);

	pci_disable_device(cx->pci_dev);

	if (cx->vbi.sliced_mpeg_data[0])
		for (i = 0; i < CX18_VBI_FRAMES; i++)
			kfree(cx->vbi.sliced_mpeg_data[i]);

	v4l2_ctrl_handler_free(&cx->av_state.hdl);

	CX18_INFO("Removed %s\n", cx->card_name);

	v4l2_device_unregister(v4l2_dev);
	kfree(cx);
}