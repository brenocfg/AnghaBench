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
struct rio_mport {TYPE_1__* outb_msg; } ;
struct TYPE_5__ {int phys; int /*<<< orphan*/  dev_id; } ;
struct fsl_rmu {TYPE_3__* msg_regs; TYPE_2__ msg_tx_ring; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  osr; int /*<<< orphan*/  odqdpar; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mcback ) (struct rio_mport*,int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 struct fsl_rmu* GET_RMM_HANDLE (struct rio_mport*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RIO_MSG_OSR_EOMI ; 
 int RIO_MSG_OSR_QOI ; 
 int RIO_MSG_OSR_TE ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  stub1 (struct rio_mport*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t
fsl_rio_tx_handler(int irq, void *dev_instance)
{
	int osr;
	struct rio_mport *port = (struct rio_mport *)dev_instance;
	struct fsl_rmu *rmu = GET_RMM_HANDLE(port);

	osr = in_be32(&rmu->msg_regs->osr);

	if (osr & RIO_MSG_OSR_TE) {
		pr_info("RIO: outbound message transmission error\n");
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_TE);
		goto out;
	}

	if (osr & RIO_MSG_OSR_QOI) {
		pr_info("RIO: outbound message queue overflow\n");
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_QOI);
		goto out;
	}

	if (osr & RIO_MSG_OSR_EOMI) {
		u32 dqp = in_be32(&rmu->msg_regs->odqdpar);
		int slot = (dqp - rmu->msg_tx_ring.phys) >> 5;
		if (port->outb_msg[0].mcback != NULL) {
			port->outb_msg[0].mcback(port, rmu->msg_tx_ring.dev_id,
					-1,
					slot);
		}
		/* Ack the end-of-message interrupt */
		out_be32(&rmu->msg_regs->osr, RIO_MSG_OSR_EOMI);
	}

out:
	return IRQ_HANDLED;
}