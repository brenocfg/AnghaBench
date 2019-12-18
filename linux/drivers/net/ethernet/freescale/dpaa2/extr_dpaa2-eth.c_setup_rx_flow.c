#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct dpni_queue_id {int /*<<< orphan*/  fqid; } ;
struct TYPE_6__ {int priority; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct dpni_queue {scalar_t__ user_context; TYPE_2__ destination; } ;
struct dpaa2_eth_priv {TYPE_4__* net_dev; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; } ;
struct dpaa2_eth_fq {TYPE_3__* channel; int /*<<< orphan*/  flowid; int /*<<< orphan*/  fqid; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device* parent; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  xdp_rxq; int /*<<< orphan*/  dpcon_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPNI_DEST_DPCON ; 
 int DPNI_QUEUE_OPT_DEST ; 
 int DPNI_QUEUE_OPT_USER_CTX ; 
 int /*<<< orphan*/  DPNI_QUEUE_RX ; 
 int /*<<< orphan*/  MEM_TYPE_PAGE_ORDER0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dpni_get_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpni_queue*,struct dpni_queue_id*) ; 
 int dpni_set_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dpni_queue*) ; 
 int xdp_rxq_info_reg (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int xdp_rxq_info_reg_mem_model (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_rx_flow(struct dpaa2_eth_priv *priv,
			 struct dpaa2_eth_fq *fq)
{
	struct device *dev = priv->net_dev->dev.parent;
	struct dpni_queue queue;
	struct dpni_queue_id qid;
	int err;

	err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, 0, fq->flowid, &queue, &qid);
	if (err) {
		dev_err(dev, "dpni_get_queue(RX) failed\n");
		return err;
	}

	fq->fqid = qid.fqid;

	queue.destination.id = fq->channel->dpcon_id;
	queue.destination.type = DPNI_DEST_DPCON;
	queue.destination.priority = 1;
	queue.user_context = (u64)(uintptr_t)fq;
	err = dpni_set_queue(priv->mc_io, 0, priv->mc_token,
			     DPNI_QUEUE_RX, 0, fq->flowid,
			     DPNI_QUEUE_OPT_USER_CTX | DPNI_QUEUE_OPT_DEST,
			     &queue);
	if (err) {
		dev_err(dev, "dpni_set_queue(RX) failed\n");
		return err;
	}

	/* xdp_rxq setup */
	err = xdp_rxq_info_reg(&fq->channel->xdp_rxq, priv->net_dev,
			       fq->flowid);
	if (err) {
		dev_err(dev, "xdp_rxq_info_reg failed\n");
		return err;
	}

	err = xdp_rxq_info_reg_mem_model(&fq->channel->xdp_rxq,
					 MEM_TYPE_PAGE_ORDER0, NULL);
	if (err) {
		dev_err(dev, "xdp_rxq_info_reg_mem_model failed\n");
		return err;
	}

	return 0;
}