#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct zynqmp_ipi_mchan {unsigned int chan_type; scalar_t__ is_opened; } ;
struct zynqmp_ipi_mbox {TYPE_1__* mchans; } ;
struct mbox_chan {struct zynqmp_ipi_mchan* con_priv; TYPE_2__* mbox; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_opened; } ;

/* Variables and functions */
 unsigned int IPI_MB_CHNL_RX ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_DISABLE_IRQ ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_RELEASE ; 
 struct zynqmp_ipi_mbox* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  zynqmp_ipi_fw_call (struct zynqmp_ipi_mbox*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static void zynqmp_ipi_shutdown(struct mbox_chan *chan)
{
	struct device *dev = chan->mbox->dev;
	struct zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	struct zynqmp_ipi_mchan *mchan = chan->con_priv;
	u64 arg0;
	struct arm_smccc_res res;
	unsigned int chan_type;

	if (!mchan->is_opened)
		return;

	/* If it is RX channel, disable notification interrupt */
	chan_type = mchan->chan_type;
	if (chan_type == IPI_MB_CHNL_RX) {
		arg0 = SMC_IPI_MAILBOX_DISABLE_IRQ;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	}
	/* Release IPI mailbox if no other channel is opened */
	chan_type = (chan_type + 1) % 2;
	if (!ipi_mbox->mchans[chan_type].is_opened) {
		arg0 = SMC_IPI_MAILBOX_RELEASE;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	}

	mchan->is_opened = 0;
}