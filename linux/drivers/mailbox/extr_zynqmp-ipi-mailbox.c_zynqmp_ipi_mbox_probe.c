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
struct zynqmp_ipi_message {int dummy; } ;
struct zynqmp_ipi_mchan {int req_buf_size; int resp_buf_size; size_t chan_type; void* rx_buf; void* resp_buf; void* req_buf; } ;
struct mbox_controller {int num_chans; int txdone_irq; int txdone_poll; int txpoll_period; struct mbox_chan* chans; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct device {int /*<<< orphan*/ * driver; int /*<<< orphan*/ * release; struct device_node* of_node; struct device* parent; } ;
struct zynqmp_ipi_mbox {struct zynqmp_ipi_mchan* mchans; struct mbox_controller mbox; int /*<<< orphan*/  remote_id; struct device dev; TYPE_1__* pdata; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct mbox_chan {struct zynqmp_ipi_mchan* con_priv; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IPI_MB_CHNL_RX ; 
 size_t IPI_MB_CHNL_TX ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct zynqmp_ipi_mbox*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 void* devm_ioremap (struct device*,int /*<<< orphan*/ ,int) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,struct mbox_controller*) ; 
 int /*<<< orphan*/  of_node_full_name (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* resource_size (struct resource*) ; 
 int /*<<< orphan*/  zynqmp_ipi_chan_ops ; 
 int /*<<< orphan*/ * zynqmp_ipi_mbox_dev_release ; 
 int /*<<< orphan*/  zynqmp_ipi_mbox_driver ; 
 int zynqmp_ipi_mbox_get_buf_res (struct device_node*,char const*,struct resource*) ; 
 int /*<<< orphan*/  zynqmp_ipi_of_xlate ; 

__attribute__((used)) static int zynqmp_ipi_mbox_probe(struct zynqmp_ipi_mbox *ipi_mbox,
				 struct device_node *node)
{
	struct zynqmp_ipi_mchan *mchan;
	struct mbox_chan *chans;
	struct mbox_controller *mbox;
	struct resource res;
	struct device *dev, *mdev;
	const char *name;
	int ret;

	dev = ipi_mbox->pdata->dev;
	/* Initialize dev for IPI mailbox */
	ipi_mbox->dev.parent = dev;
	ipi_mbox->dev.release = NULL;
	ipi_mbox->dev.of_node = node;
	dev_set_name(&ipi_mbox->dev, "%s", of_node_full_name(node));
	dev_set_drvdata(&ipi_mbox->dev, ipi_mbox);
	ipi_mbox->dev.release = zynqmp_ipi_mbox_dev_release;
	ipi_mbox->dev.driver = &zynqmp_ipi_mbox_driver;
	ret = device_register(&ipi_mbox->dev);
	if (ret) {
		dev_err(dev, "Failed to register ipi mbox dev.\n");
		return ret;
	}
	mdev = &ipi_mbox->dev;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNL_TX];
	name = "local_request_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	if (!ret) {
		mchan->req_buf_size = resource_size(&res);
		mchan->req_buf = devm_ioremap(mdev, res.start,
					      mchan->req_buf_size);
		if (IS_ERR(mchan->req_buf)) {
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			ret = PTR_ERR(mchan->req_buf);
			return ret;
		}
	} else if (ret != -ENODEV) {
		dev_err(mdev, "Unmatched resource %s, %d.\n", name, ret);
		return ret;
	}

	name = "remote_response_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	if (!ret) {
		mchan->resp_buf_size = resource_size(&res);
		mchan->resp_buf = devm_ioremap(mdev, res.start,
					       mchan->resp_buf_size);
		if (IS_ERR(mchan->resp_buf)) {
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			ret = PTR_ERR(mchan->resp_buf);
			return ret;
		}
	} else if (ret != -ENODEV) {
		dev_err(mdev, "Unmatched resource %s.\n", name);
		return ret;
	}
	mchan->rx_buf = devm_kzalloc(mdev,
				     mchan->resp_buf_size +
				     sizeof(struct zynqmp_ipi_message),
				     GFP_KERNEL);
	if (!mchan->rx_buf)
		return -ENOMEM;

	mchan = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
	name = "remote_request_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	if (!ret) {
		mchan->req_buf_size = resource_size(&res);
		mchan->req_buf = devm_ioremap(mdev, res.start,
					      mchan->req_buf_size);
		if (IS_ERR(mchan->req_buf)) {
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			ret = PTR_ERR(mchan->req_buf);
			return ret;
		}
	} else if (ret != -ENODEV) {
		dev_err(mdev, "Unmatched resource %s.\n", name);
		return ret;
	}

	name = "local_response_region";
	ret = zynqmp_ipi_mbox_get_buf_res(node, name, &res);
	if (!ret) {
		mchan->resp_buf_size = resource_size(&res);
		mchan->resp_buf = devm_ioremap(mdev, res.start,
					       mchan->resp_buf_size);
		if (IS_ERR(mchan->resp_buf)) {
			dev_err(mdev, "Unable to map IPI buffer I/O memory\n");
			ret = PTR_ERR(mchan->resp_buf);
			return ret;
		}
	} else if (ret != -ENODEV) {
		dev_err(mdev, "Unmatched resource %s.\n", name);
		return ret;
	}
	mchan->rx_buf = devm_kzalloc(mdev,
				     mchan->resp_buf_size +
				     sizeof(struct zynqmp_ipi_message),
				     GFP_KERNEL);
	if (!mchan->rx_buf)
		return -ENOMEM;

	/* Get the IPI remote agent ID */
	ret = of_property_read_u32(node, "xlnx,ipi-id", &ipi_mbox->remote_id);
	if (ret < 0) {
		dev_err(dev, "No IPI remote ID is specified.\n");
		return ret;
	}

	mbox = &ipi_mbox->mbox;
	mbox->dev = mdev;
	mbox->ops = &zynqmp_ipi_chan_ops;
	mbox->num_chans = 2;
	mbox->txdone_irq = false;
	mbox->txdone_poll = true;
	mbox->txpoll_period = 5;
	mbox->of_xlate = zynqmp_ipi_of_xlate;
	chans = devm_kzalloc(mdev, 2 * sizeof(*chans), GFP_KERNEL);
	if (!chans)
		return -ENOMEM;
	mbox->chans = chans;
	chans[IPI_MB_CHNL_TX].con_priv = &ipi_mbox->mchans[IPI_MB_CHNL_TX];
	chans[IPI_MB_CHNL_RX].con_priv = &ipi_mbox->mchans[IPI_MB_CHNL_RX];
	ipi_mbox->mchans[IPI_MB_CHNL_TX].chan_type = IPI_MB_CHNL_TX;
	ipi_mbox->mchans[IPI_MB_CHNL_RX].chan_type = IPI_MB_CHNL_RX;
	ret = devm_mbox_controller_register(mdev, mbox);
	if (ret)
		dev_err(mdev,
			"Failed to register mbox_controller(%d)\n", ret);
	else
		dev_info(mdev,
			 "Registered ZynqMP IPI mbox with TX/RX channels.\n");
	return ret;
}