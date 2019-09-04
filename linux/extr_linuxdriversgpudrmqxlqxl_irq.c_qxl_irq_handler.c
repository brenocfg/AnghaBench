#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct qxl_device {scalar_t__ io_base; TYPE_1__* ram_header; int /*<<< orphan*/  client_monitors_config_work; int /*<<< orphan*/  irq_received_error; int /*<<< orphan*/  io_cmd_event; int /*<<< orphan*/  irq_received_io_cmd; int /*<<< orphan*/  cursor_event; int /*<<< orphan*/  irq_received_cursor; int /*<<< orphan*/  display_event; int /*<<< orphan*/  irq_received_display; int /*<<< orphan*/  irq_received; } ;
struct drm_device {scalar_t__ dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  int_mask; int /*<<< orphan*/  int_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARN (char*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int QXL_INTERRUPT_CLIENT_MONITORS_CONFIG ; 
 int QXL_INTERRUPT_CURSOR ; 
 int QXL_INTERRUPT_DISPLAY ; 
 int QXL_INTERRUPT_ERROR ; 
 int QXL_INTERRUPT_IO_CMD ; 
 int /*<<< orphan*/  QXL_INTERRUPT_MASK ; 
 scalar_t__ QXL_IO_UPDATE_IRQ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qxl_queue_garbage_collect (struct qxl_device*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

irqreturn_t qxl_irq_handler(int irq, void *arg)
{
	struct drm_device *dev = (struct drm_device *) arg;
	struct qxl_device *qdev = (struct qxl_device *)dev->dev_private;
	uint32_t pending;

	pending = xchg(&qdev->ram_header->int_pending, 0);

	if (!pending)
		return IRQ_NONE;

	atomic_inc(&qdev->irq_received);

	if (pending & QXL_INTERRUPT_DISPLAY) {
		atomic_inc(&qdev->irq_received_display);
		wake_up_all(&qdev->display_event);
		qxl_queue_garbage_collect(qdev, false);
	}
	if (pending & QXL_INTERRUPT_CURSOR) {
		atomic_inc(&qdev->irq_received_cursor);
		wake_up_all(&qdev->cursor_event);
	}
	if (pending & QXL_INTERRUPT_IO_CMD) {
		atomic_inc(&qdev->irq_received_io_cmd);
		wake_up_all(&qdev->io_cmd_event);
	}
	if (pending & QXL_INTERRUPT_ERROR) {
		/* TODO: log it, reset device (only way to exit this condition)
		 * (do it a certain number of times, afterwards admit defeat,
		 * to avoid endless loops).
		 */
		qdev->irq_received_error++;
		DRM_WARN("driver is in bug mode\n");
	}
	if (pending & QXL_INTERRUPT_CLIENT_MONITORS_CONFIG) {
		schedule_work(&qdev->client_monitors_config_work);
	}
	qdev->ram_header->int_mask = QXL_INTERRUPT_MASK;
	outb(0, qdev->io_base + QXL_IO_UPDATE_IRQ);
	return IRQ_HANDLED;
}