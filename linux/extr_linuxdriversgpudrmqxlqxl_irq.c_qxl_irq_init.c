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
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct qxl_device {TYPE_2__* ram_header; TYPE_3__ ddev; scalar_t__ irq_received_error; int /*<<< orphan*/  irq_received_io_cmd; int /*<<< orphan*/  irq_received_cursor; int /*<<< orphan*/  irq_received_display; int /*<<< orphan*/  irq_received; int /*<<< orphan*/  client_monitors_config_work; int /*<<< orphan*/  io_cmd_event; int /*<<< orphan*/  cursor_event; int /*<<< orphan*/  display_event; } ;
struct TYPE_5__ {int /*<<< orphan*/  int_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QXL_INTERRUPT_MASK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_irq_install (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_client_monitors_config_work_func ; 
 scalar_t__ unlikely (int) ; 

int qxl_irq_init(struct qxl_device *qdev)
{
	int ret;

	init_waitqueue_head(&qdev->display_event);
	init_waitqueue_head(&qdev->cursor_event);
	init_waitqueue_head(&qdev->io_cmd_event);
	INIT_WORK(&qdev->client_monitors_config_work,
		  qxl_client_monitors_config_work_func);
	atomic_set(&qdev->irq_received, 0);
	atomic_set(&qdev->irq_received_display, 0);
	atomic_set(&qdev->irq_received_cursor, 0);
	atomic_set(&qdev->irq_received_io_cmd, 0);
	qdev->irq_received_error = 0;
	ret = drm_irq_install(&qdev->ddev, qdev->ddev.pdev->irq);
	qdev->ram_header->int_mask = QXL_INTERRUPT_MASK;
	if (unlikely(ret != 0)) {
		DRM_ERROR("Failed installing irq: %d\n", ret);
		return 1;
	}
	return 0;
}