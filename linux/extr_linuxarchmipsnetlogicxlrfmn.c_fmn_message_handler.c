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
typedef  int uint32_t ;
struct nlm_fmn_msg {int dummy; } ;
struct fmn_message_handler {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* action ) (int,int,int,int,struct nlm_fmn_msg*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct fmn_message_handler* msg_handlers ; 
 int /*<<< orphan*/  nlm_cop2_disable_irqrestore (int) ; 
 int nlm_cop2_enable_irqsave () ; 
 int nlm_fmn_receive (int,int*,int*,int*,struct nlm_fmn_msg*) ; 
 int /*<<< orphan*/  nlm_fmn_setup_intr (int,int) ; 
 int nlm_read_c2_status0 () ; 
 int nlm_threads_per_core ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  stub1 (int,int,int,int,struct nlm_fmn_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fmn_message_handler(int irq, void *data)
{
	struct fmn_message_handler *hndlr;
	int bucket, rv;
	int size = 0, code = 0, src_stnid = 0;
	struct nlm_fmn_msg msg;
	uint32_t mflags, bkt_status;

	mflags = nlm_cop2_enable_irqsave();
	/* Disable message ring interrupt */
	nlm_fmn_setup_intr(irq, 0);
	while (1) {
		/* 8 bkts per core, [24:31] each bit represents one bucket
		 * Bit is Zero if bucket is not empty */
		bkt_status = (nlm_read_c2_status0() >> 24) & 0xff;
		if (bkt_status == 0xff)
			break;
		for (bucket = 0; bucket < 8; bucket++) {
			/* Continue on empty bucket */
			if (bkt_status & (1 << bucket))
				continue;
			rv = nlm_fmn_receive(bucket, &size, &code, &src_stnid,
						&msg);
			if (rv != 0)
				continue;

			hndlr = &msg_handlers[src_stnid];
			if (hndlr->action == NULL)
				pr_warn("No msgring handler for stnid %d\n",
						src_stnid);
			else {
				nlm_cop2_disable_irqrestore(mflags);
				hndlr->action(bucket, src_stnid, size, code,
					&msg, hndlr->arg);
				mflags = nlm_cop2_enable_irqsave();
			}
		}
	};
	/* Enable message ring intr, to any thread in core */
	nlm_fmn_setup_intr(irq, (1 << nlm_threads_per_core) - 1);
	nlm_cop2_disable_irqrestore(mflags);
	return IRQ_HANDLED;
}