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
struct qcom_slim_ngd_ctrl {int /*<<< orphan*/  dma_tx_channel; int /*<<< orphan*/  tx_buf_lock; scalar_t__ tx_head; scalar_t__ tx_tail; int /*<<< orphan*/  tx_base; int /*<<< orphan*/  tx_phys_base; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QCOM_SLIM_NGD_DESC_NUM ; 
 int SLIM_MSGQ_BUF_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_request_slave_channel (struct device*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int qcom_slim_ngd_init_tx_msgq(struct qcom_slim_ngd_ctrl *ctrl)
{
	struct device *dev = ctrl->dev;
	unsigned long flags;
	int ret = 0;
	int size;

	ctrl->dma_tx_channel = dma_request_slave_channel(dev, "tx");
	if (!ctrl->dma_tx_channel) {
		dev_err(dev, "Failed to request dma channels");
		return -EINVAL;
	}

	size = ((QCOM_SLIM_NGD_DESC_NUM + 1) * SLIM_MSGQ_BUF_LEN);
	ctrl->tx_base = dma_alloc_coherent(dev, size, &ctrl->tx_phys_base,
					   GFP_KERNEL);
	if (!ctrl->tx_base) {
		dev_err(dev, "dma_alloc_coherent failed\n");
		ret = -EINVAL;
		goto rel_tx;
	}

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);
	ctrl->tx_tail = 0;
	ctrl->tx_head = 0;
	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);

	return 0;
rel_tx:
	dma_release_channel(ctrl->dma_tx_channel);
	return ret;
}