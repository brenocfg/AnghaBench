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
struct zynqmp_ipi_mchan {int is_opened; int chan_type; } ;
struct zynqmp_ipi_mbox {TYPE_2__* mchans; } ;
struct mbox_chan {struct zynqmp_ipi_mchan* con_priv; TYPE_1__* mbox; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int a0; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_opened; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int IPI_MB_CHNL_RX ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_ENABLE_IRQ ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_OPEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct zynqmp_ipi_mbox* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  zynqmp_ipi_fw_call (struct zynqmp_ipi_mbox*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int zynqmp_ipi_startup(struct mbox_chan *chan)
{
	struct device *dev = chan->mbox->dev;
	struct zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	struct zynqmp_ipi_mchan *mchan = chan->con_priv;
	u64 arg0;
	struct arm_smccc_res res;
	int ret = 0;
	unsigned int nchan_type;

	if (mchan->is_opened)
		return 0;

	/* If no channel has been opened, open the IPI mailbox */
	nchan_type = (mchan->chan_type + 1) % 2;
	if (!ipi_mbox->mchans[nchan_type].is_opened) {
		arg0 = SMC_IPI_MAILBOX_OPEN;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
		/* Check the SMC call status, a0 of the result */
		ret = (int)(res.a0 & 0xFFFFFFFF);
		if (ret < 0) {
			dev_err(dev, "SMC to open the IPI channel failed.\n");
			return ret;
		}
		ret = 0;
	}

	/* If it is RX channel, enable the IPI notification interrupt */
	if (mchan->chan_type == IPI_MB_CHNL_RX) {
		arg0 = SMC_IPI_MAILBOX_ENABLE_IRQ;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	}
	mchan->is_opened = 1;

	return ret;
}