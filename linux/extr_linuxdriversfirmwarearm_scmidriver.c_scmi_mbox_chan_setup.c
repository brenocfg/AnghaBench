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
struct scmi_info {int /*<<< orphan*/  handle; int /*<<< orphan*/  tx_idr; int /*<<< orphan*/  dev; } ;
struct mbox_client {int tx_block; int knows_txdone; int /*<<< orphan*/  tx_prepare; int /*<<< orphan*/  rx_callback; struct device* dev; } ;
struct scmi_chan_info {int /*<<< orphan*/ * handle; int /*<<< orphan*/  chan; int /*<<< orphan*/  payload; struct mbox_client cl; struct device* dev; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCMI_PROTOCOL_BASE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct scmi_chan_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct scmi_chan_info*,int,int,int /*<<< orphan*/ ) ; 
 struct scmi_chan_info* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_request_channel (struct mbox_client*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 scalar_t__ scmi_mailbox_check (struct device_node*) ; 
 int /*<<< orphan*/  scmi_rx_callback ; 
 int /*<<< orphan*/  scmi_tx_prepare ; 

__attribute__((used)) static inline int
scmi_mbox_chan_setup(struct scmi_info *info, struct device *dev, int prot_id)
{
	int ret;
	struct resource res;
	resource_size_t size;
	struct device_node *shmem, *np = dev->of_node;
	struct scmi_chan_info *cinfo;
	struct mbox_client *cl;

	if (scmi_mailbox_check(np)) {
		cinfo = idr_find(&info->tx_idr, SCMI_PROTOCOL_BASE);
		goto idr_alloc;
	}

	cinfo = devm_kzalloc(info->dev, sizeof(*cinfo), GFP_KERNEL);
	if (!cinfo)
		return -ENOMEM;

	cinfo->dev = dev;

	cl = &cinfo->cl;
	cl->dev = dev;
	cl->rx_callback = scmi_rx_callback;
	cl->tx_prepare = scmi_tx_prepare;
	cl->tx_block = false;
	cl->knows_txdone = true;

	shmem = of_parse_phandle(np, "shmem", 0);
	ret = of_address_to_resource(shmem, 0, &res);
	of_node_put(shmem);
	if (ret) {
		dev_err(dev, "failed to get SCMI Tx payload mem resource\n");
		return ret;
	}

	size = resource_size(&res);
	cinfo->payload = devm_ioremap(info->dev, res.start, size);
	if (!cinfo->payload) {
		dev_err(dev, "failed to ioremap SCMI Tx payload\n");
		return -EADDRNOTAVAIL;
	}

	/* Transmit channel is first entry i.e. index 0 */
	cinfo->chan = mbox_request_channel(cl, 0);
	if (IS_ERR(cinfo->chan)) {
		ret = PTR_ERR(cinfo->chan);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request SCMI Tx mailbox\n");
		return ret;
	}

idr_alloc:
	ret = idr_alloc(&info->tx_idr, cinfo, prot_id, prot_id + 1, GFP_KERNEL);
	if (ret != prot_id) {
		dev_err(dev, "unable to allocate SCMI idr slot err %d\n", ret);
		return ret;
	}

	cinfo->handle = &info->handle;
	return 0;
}