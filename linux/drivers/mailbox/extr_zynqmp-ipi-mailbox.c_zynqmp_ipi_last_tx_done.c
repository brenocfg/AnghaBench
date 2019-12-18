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
struct zynqmp_ipi_mchan {scalar_t__ chan_type; } ;
struct zynqmp_ipi_mbox {int dummy; } ;
struct mbox_chan {struct zynqmp_ipi_mchan* con_priv; TYPE_1__* mbox; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a0; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 scalar_t__ IPI_MB_CHNL_TX ; 
 int IPI_MB_STATUS_SEND_PENDING ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_STATUS_ENQUIRY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct zynqmp_ipi_mbox* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  zynqmp_ipi_fw_call (struct zynqmp_ipi_mbox*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static bool zynqmp_ipi_last_tx_done(struct mbox_chan *chan)
{
	struct device *dev = chan->mbox->dev;
	struct zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	struct zynqmp_ipi_mchan *mchan = chan->con_priv;
	int ret;
	u64 arg0;
	struct arm_smccc_res res;

	if (WARN_ON(!ipi_mbox)) {
		dev_err(dev, "no platform drv data??\n");
		return false;
	}

	if (mchan->chan_type == IPI_MB_CHNL_TX) {
		/* We only need to check if the message been taken
		 * by the remote in the TX channel
		 */
		arg0 = SMC_IPI_MAILBOX_STATUS_ENQUIRY;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
		/* Check the SMC call status, a0 of the result */
		ret = (int)(res.a0 & 0xFFFFFFFF);
		if (ret < 0 || ret & IPI_MB_STATUS_SEND_PENDING)
			return false;
		return true;
	}
	/* Always true for the response message in RX channel */
	return true;
}