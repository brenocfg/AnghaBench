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
struct zynqmp_ipi_message {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct zynqmp_ipi_mchan {scalar_t__ chan_type; scalar_t__ req_buf_size; scalar_t__ resp_buf_size; int /*<<< orphan*/  resp_buf; int /*<<< orphan*/  req_buf; } ;
struct zynqmp_ipi_mbox {int dummy; } ;
struct mbox_chan {struct zynqmp_ipi_mchan* con_priv; TYPE_1__* mbox; } ;
struct device {int dummy; } ;
struct arm_smccc_res {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPI_MB_CHNL_TX ; 
 int /*<<< orphan*/  IPI_SMC_ACK_EIRQ_MASK ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_ACK ; 
 int /*<<< orphan*/  SMC_IPI_MAILBOX_NOTIFY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct zynqmp_ipi_mbox* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zynqmp_ipi_fw_call (struct zynqmp_ipi_mbox*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 

__attribute__((used)) static int zynqmp_ipi_send_data(struct mbox_chan *chan, void *data)
{
	struct device *dev = chan->mbox->dev;
	struct zynqmp_ipi_mbox *ipi_mbox = dev_get_drvdata(dev);
	struct zynqmp_ipi_mchan *mchan = chan->con_priv;
	struct zynqmp_ipi_message *msg = data;
	u64 arg0;
	struct arm_smccc_res res;

	if (WARN_ON(!ipi_mbox)) {
		dev_err(dev, "no platform drv data??\n");
		return -EINVAL;
	}

	if (mchan->chan_type == IPI_MB_CHNL_TX) {
		/* Send request message */
		if (msg && msg->len > mchan->req_buf_size) {
			dev_err(dev, "channel %d message length %u > max %lu\n",
				mchan->chan_type, (unsigned int)msg->len,
				mchan->req_buf_size);
			return -EINVAL;
		}
		if (msg && msg->len)
			memcpy_toio(mchan->req_buf, msg->data, msg->len);
		/* Kick IPI mailbox to send message */
		arg0 = SMC_IPI_MAILBOX_NOTIFY;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, 0, &res);
	} else {
		/* Send response message */
		if (msg && msg->len > mchan->resp_buf_size) {
			dev_err(dev, "channel %d message length %u > max %lu\n",
				mchan->chan_type, (unsigned int)msg->len,
				mchan->resp_buf_size);
			return -EINVAL;
		}
		if (msg && msg->len)
			memcpy_toio(mchan->resp_buf, msg->data, msg->len);
		arg0 = SMC_IPI_MAILBOX_ACK;
		zynqmp_ipi_fw_call(ipi_mbox, arg0, IPI_SMC_ACK_EIRQ_MASK,
				   &res);
	}
	return 0;
}