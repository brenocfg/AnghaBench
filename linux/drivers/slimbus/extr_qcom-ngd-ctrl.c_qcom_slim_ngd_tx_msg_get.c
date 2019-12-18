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
typedef  int /*<<< orphan*/  u32 ;
struct qcom_slim_ngd_dma_desc {int /*<<< orphan*/ * base; struct completion* comp; } ;
struct qcom_slim_ngd_ctrl {int tx_tail; int tx_head; int /*<<< orphan*/  tx_buf_lock; int /*<<< orphan*/ * tx_base; struct qcom_slim_ngd_dma_desc* txdesc; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int QCOM_SLIM_NGD_DESC_NUM ; 
 int SLIM_MSGQ_BUF_LEN ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 *qcom_slim_ngd_tx_msg_get(struct qcom_slim_ngd_ctrl *ctrl, int len,
				     struct completion *comp)
{
	struct qcom_slim_ngd_dma_desc *desc;
	unsigned long flags;

	spin_lock_irqsave(&ctrl->tx_buf_lock, flags);

	if ((ctrl->tx_tail + 1) % QCOM_SLIM_NGD_DESC_NUM == ctrl->tx_head) {
		spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);
		return NULL;
	}
	desc  = &ctrl->txdesc[ctrl->tx_tail];
	desc->base = ctrl->tx_base + ctrl->tx_tail * SLIM_MSGQ_BUF_LEN;
	desc->comp = comp;
	ctrl->tx_tail = (ctrl->tx_tail + 1) % QCOM_SLIM_NGD_DESC_NUM;

	spin_unlock_irqrestore(&ctrl->tx_buf_lock, flags);

	return desc->base;
}