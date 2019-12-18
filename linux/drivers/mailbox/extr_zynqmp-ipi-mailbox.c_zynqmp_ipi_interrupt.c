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
typedef  int /*<<< orphan*/  u64 ;
struct zynqmp_ipi_pdata {int num_mboxes; struct zynqmp_ipi_mbox* ipi_mboxes; } ;
struct zynqmp_ipi_message {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct zynqmp_ipi_mchan {int /*<<< orphan*/  req_buf; int /*<<< orphan*/  req_buf_size; struct zynqmp_ipi_message* rx_buf; scalar_t__ is_opened; } ;
struct TYPE_2__ {struct mbox_chan* chans; } ;
struct zynqmp_ipi_mbox {TYPE_1__ mbox; struct zynqmp_ipi_mchan* mchans; } ;
struct mbox_chan {int dummy; } ;
struct arm_smccc_res {int a0; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t IPI_MB_CHNL_RX ; 
 int IPI_MB_STATUS_RECV_PENDING ; 
 int /*<<< orphan*/  IPI_SMC_ENQUIRY_DIRQ_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_STATUS_ENQUIRY ; 
 int /*<<< orphan*/  mbox_chan_received_data (struct mbox_chan*,void*) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_ipi_fw_call (struct zynqmp_ipi_mbox*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static irqreturn_t zynqmp_ipi_interrupt(int irq, void *data)
{
	struct zynqmp_ipi_pdata *pdata = data;
	struct mbox_chan *chan;
	struct zynqmp_ipi_mbox *ipi_mbox;
	struct zynqmp_ipi_mchan *mchan;
	struct zynqmp_ipi_message *msg;
	u64 arg0, arg3;
	struct arm_smccc_res res;
	int ret, i;

	(void)irq;
	arg0 = SMC_IPI_MAILBOX_STATUS_ENQUIRY;
	arg3 = IPI_SMC_ENQUIRY_DIRQ_MASK;
	for (i = 0; i < pdata->num_mboxes; i++) {
		ipi_mbox = &pdata->ipi_mboxes[i];
		mchan = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
		chan = &ipi_mbox->mbox.chans[IPI_MB_CHNL_RX];
		zynqmp_ipi_fw_call(ipi_mbox, arg0, arg3, &res);
		ret = (int)(res.a0 & 0xFFFFFFFF);
		if (ret > 0 && ret & IPI_MB_STATUS_RECV_PENDING) {
			if (mchan->is_opened) {
				msg = mchan->rx_buf;
				msg->len = mchan->req_buf_size;
				memcpy_fromio(msg->data, mchan->req_buf,
					      msg->len);
				mbox_chan_received_data(chan, (void *)msg);
				return IRQ_HANDLED;
			}
		}
	}
	return IRQ_NONE;
}