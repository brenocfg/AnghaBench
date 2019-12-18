#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_num; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc_num; } ;
struct TYPE_5__ {TYPE_3__ csq; int /*<<< orphan*/  tx_timeout; TYPE_1__ crq; } ;
struct hns_roce_v2_priv {TYPE_2__ cmq; } ;
struct hns_roce_dev {int /*<<< orphan*/  dev; scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_CRQ_DESC_NUM ; 
 int /*<<< orphan*/  CMD_CSQ_DESC_NUM ; 
 int /*<<< orphan*/  HNS_ROCE_CMQ_TX_TIMEOUT ; 
 int /*<<< orphan*/  TYPE_CRQ ; 
 int /*<<< orphan*/  TYPE_CSQ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_init_regs (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_free_cmq_desc (struct hns_roce_dev*,TYPE_3__*) ; 
 int hns_roce_init_cmq_ring (struct hns_roce_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_v2_cmq_init(struct hns_roce_dev *hr_dev)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	int ret;

	/* Setup the queue entries for command queue */
	priv->cmq.csq.desc_num = CMD_CSQ_DESC_NUM;
	priv->cmq.crq.desc_num = CMD_CRQ_DESC_NUM;

	/* Setup the lock for command queue */
	spin_lock_init(&priv->cmq.csq.lock);
	spin_lock_init(&priv->cmq.crq.lock);

	/* Setup Tx write back timeout */
	priv->cmq.tx_timeout = HNS_ROCE_CMQ_TX_TIMEOUT;

	/* Init CSQ */
	ret = hns_roce_init_cmq_ring(hr_dev, TYPE_CSQ);
	if (ret) {
		dev_err(hr_dev->dev, "Init CSQ error, ret = %d.\n", ret);
		return ret;
	}

	/* Init CRQ */
	ret = hns_roce_init_cmq_ring(hr_dev, TYPE_CRQ);
	if (ret) {
		dev_err(hr_dev->dev, "Init CRQ error, ret = %d.\n", ret);
		goto err_crq;
	}

	/* Init CSQ REG */
	hns_roce_cmq_init_regs(hr_dev, TYPE_CSQ);

	/* Init CRQ REG */
	hns_roce_cmq_init_regs(hr_dev, TYPE_CRQ);

	return 0;

err_crq:
	hns_roce_free_cmq_desc(hr_dev, &priv->cmq.csq);

	return ret;
}