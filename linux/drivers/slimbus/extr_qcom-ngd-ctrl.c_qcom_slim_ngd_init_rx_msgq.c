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
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dma_rx_channel; int /*<<< orphan*/  rx_phys_base; int /*<<< orphan*/  rx_base; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QCOM_SLIM_NGD_DESC_NUM ; 
 int SLIM_MSGQ_BUF_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel (struct device*,char*) ; 
 int qcom_slim_ngd_post_rx_msgq (struct qcom_slim_ngd_ctrl*) ; 

__attribute__((used)) static int qcom_slim_ngd_init_rx_msgq(struct qcom_slim_ngd_ctrl *ctrl)
{
	struct device *dev = ctrl->dev;
	int ret, size;

	ctrl->dma_rx_channel = dma_request_slave_channel(dev, "rx");
	if (!ctrl->dma_rx_channel) {
		dev_err(dev, "Failed to request dma channels");
		return -EINVAL;
	}

	size = QCOM_SLIM_NGD_DESC_NUM * SLIM_MSGQ_BUF_LEN;
	ctrl->rx_base = dma_alloc_coherent(dev, size, &ctrl->rx_phys_base,
					   GFP_KERNEL);
	if (!ctrl->rx_base) {
		dev_err(dev, "dma_alloc_coherent failed\n");
		ret = -ENOMEM;
		goto rel_rx;
	}

	ret = qcom_slim_ngd_post_rx_msgq(ctrl);
	if (ret) {
		dev_err(dev, "post_rx_msgq() failed 0x%x\n", ret);
		goto rx_post_err;
	}

	return 0;

rx_post_err:
	dma_free_coherent(dev, size, ctrl->rx_base, ctrl->rx_phys_base);
rel_rx:
	dma_release_channel(ctrl->dma_rx_channel);
	return ret;
}