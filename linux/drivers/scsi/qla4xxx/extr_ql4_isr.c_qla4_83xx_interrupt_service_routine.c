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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {TYPE_1__* qla4_83xx_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  mb_int_mask; int /*<<< orphan*/  risc_intr; int /*<<< orphan*/ * mailbox_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4xxx_isr_decode_mailbox (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla4xxx_process_response_queue (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4_83xx_interrupt_service_routine(struct scsi_qla_host *ha,
					 uint32_t intr_status)
{
	/* Process mailbox/asynch event interrupt.*/
	if (intr_status) {
		qla4xxx_isr_decode_mailbox(ha,
				readl(&ha->qla4_83xx_reg->mailbox_out[0]));
		/* clear the interrupt */
		writel(0, &ha->qla4_83xx_reg->risc_intr);
	} else {
		qla4xxx_process_response_queue(ha);
	}

	/* clear the interrupt */
	writel(0, &ha->qla4_83xx_reg->mb_int_mask);
}