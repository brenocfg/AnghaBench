#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * reg; } ;
struct TYPE_8__ {int header_type; int /*<<< orphan*/  header_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  error_code; } ;
struct TYPE_10__ {TYPE_4__ irq; TYPE_3__ common; int /*<<< orphan*/  status; TYPE_2__ error; } ;
struct vub300_mmc_host {int irqs_queued; int irq_disabled; int /*<<< orphan*/  irq_mutex; int /*<<< orphan*/  mmc; int /*<<< orphan*/  irq_enabled; TYPE_5__ resp; int /*<<< orphan*/  card_present; int /*<<< orphan*/  system_port_status; TYPE_1__* command_res_urb; } ;
struct TYPE_6__ {scalar_t__ actual_length; } ;

/* Variables and functions */
 int HZ ; 
#define  RESPONSE_ERROR 133 
#define  RESPONSE_INTERRUPT 132 
#define  RESPONSE_IRQ_DISABLED 131 
#define  RESPONSE_IRQ_ENABLED 130 
#define  RESPONSE_NO_INTERRUPT 129 
#define  RESPONSE_STATUS 128 
 int /*<<< orphan*/  SD_ERROR_NO_DEVICE ; 
 int /*<<< orphan*/  add_offloaded_reg (struct vub300_mmc_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_vub300_port_status (struct vub300_mmc_host*) ; 
 int /*<<< orphan*/  mmc_signal_sdio_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_system_port_status (struct vub300_mmc_host*) ; 
 int /*<<< orphan*/  vub300_queue_poll_work (struct vub300_mmc_host*,int) ; 

__attribute__((used)) static void __vub300_irqpoll_response(struct vub300_mmc_host *vub300)
{
	/* cmd_mutex is held by vub300_pollwork_thread */
	if (vub300->command_res_urb->actual_length == 0)
		return;

	switch (vub300->resp.common.header_type) {
	case RESPONSE_INTERRUPT:
		mutex_lock(&vub300->irq_mutex);
		if (vub300->irq_enabled)
			mmc_signal_sdio_irq(vub300->mmc);
		else
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 1;
		mutex_unlock(&vub300->irq_mutex);
		break;
	case RESPONSE_ERROR:
		if (vub300->resp.error.error_code == SD_ERROR_NO_DEVICE)
			check_vub300_port_status(vub300);
		break;
	case RESPONSE_STATUS:
		vub300->system_port_status = vub300->resp.status;
		new_system_port_status(vub300);
		if (!vub300->card_present)
			vub300_queue_poll_work(vub300, HZ / 5);
		break;
	case RESPONSE_IRQ_DISABLED:
	{
		int offloaded_data_length = vub300->resp.common.header_size - 3;
		int register_count = offloaded_data_length >> 3;
		int ri = 0;
		while (register_count--) {
			add_offloaded_reg(vub300, &vub300->resp.irq.reg[ri]);
			ri += 1;
		}
		mutex_lock(&vub300->irq_mutex);
		if (vub300->irq_enabled)
			mmc_signal_sdio_irq(vub300->mmc);
		else
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 1;
		mutex_unlock(&vub300->irq_mutex);
		break;
	}
	case RESPONSE_IRQ_ENABLED:
	{
		int offloaded_data_length = vub300->resp.common.header_size - 3;
		int register_count = offloaded_data_length >> 3;
		int ri = 0;
		while (register_count--) {
			add_offloaded_reg(vub300, &vub300->resp.irq.reg[ri]);
			ri += 1;
		}
		mutex_lock(&vub300->irq_mutex);
		if (vub300->irq_enabled)
			mmc_signal_sdio_irq(vub300->mmc);
		else
			vub300->irqs_queued += 1;
		vub300->irq_disabled = 0;
		mutex_unlock(&vub300->irq_mutex);
		break;
	}
	case RESPONSE_NO_INTERRUPT:
		vub300_queue_poll_work(vub300, 1);
		break;
	default:
		break;
	}
}