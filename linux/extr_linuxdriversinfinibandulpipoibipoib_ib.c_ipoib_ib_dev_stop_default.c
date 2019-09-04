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
struct net_device {int dummy; } ;
struct ipoib_tx_buf {int /*<<< orphan*/ * skb; } ;
struct ipoib_rx_buf {int /*<<< orphan*/ * skb; int /*<<< orphan*/  mapping; } ;
struct ipoib_dev_priv {int tx_head; int tx_tail; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  qp; struct ipoib_rx_buf* rx_ring; struct ipoib_tx_buf* tx_ring; int /*<<< orphan*/  flags; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  IB_QPS_ERR ; 
 int /*<<< orphan*/  IB_QPS_RESET ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  check_qp_movement_and_print (struct ipoib_dev_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 scalar_t__ ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_dev_stop (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_dma_unmap_tx (struct ipoib_dev_priv*,struct ipoib_tx_buf*) ; 
 int /*<<< orphan*/  ipoib_drain_cq (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_napi_disable (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int ipoib_recvq_size ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_ud_dma_unmap_rx (struct ipoib_dev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 unsigned long jiffies ; 
 scalar_t__ recvs_pending (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int ipoib_ib_dev_stop_default(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ib_qp_attr qp_attr;
	unsigned long begin;
	struct ipoib_tx_buf *tx_req;
	int i;

	if (test_bit(IPOIB_FLAG_INITIALIZED, &priv->flags))
		ipoib_napi_disable(dev);

	ipoib_cm_dev_stop(dev);

	/*
	 * Move our QP to the error state and then reinitialize in
	 * when all work requests have completed or have been flushed.
	 */
	qp_attr.qp_state = IB_QPS_ERR;
	if (ib_modify_qp(priv->qp, &qp_attr, IB_QP_STATE))
		check_qp_movement_and_print(priv, priv->qp, IB_QPS_ERR);

	/* Wait for all sends and receives to complete */
	begin = jiffies;

	while (priv->tx_head != priv->tx_tail || recvs_pending(dev)) {
		if (time_after(jiffies, begin + 5 * HZ)) {
			ipoib_warn(priv,
				   "timing out; %d sends %d receives not completed\n",
				   priv->tx_head - priv->tx_tail,
				   recvs_pending(dev));

			/*
			 * assume the HW is wedged and just free up
			 * all our pending work requests.
			 */
			while ((int)priv->tx_tail - (int)priv->tx_head < 0) {
				tx_req = &priv->tx_ring[priv->tx_tail &
							(ipoib_sendq_size - 1)];
				ipoib_dma_unmap_tx(priv, tx_req);
				dev_kfree_skb_any(tx_req->skb);
				++priv->tx_tail;
			}

			for (i = 0; i < ipoib_recvq_size; ++i) {
				struct ipoib_rx_buf *rx_req;

				rx_req = &priv->rx_ring[i];
				if (!rx_req->skb)
					continue;
				ipoib_ud_dma_unmap_rx(priv,
						      priv->rx_ring[i].mapping);
				dev_kfree_skb_any(rx_req->skb);
				rx_req->skb = NULL;
			}

			goto timeout;
		}

		ipoib_drain_cq(dev);

		usleep_range(1000, 2000);
	}

	ipoib_dbg(priv, "All sends and receives done.\n");

timeout:
	qp_attr.qp_state = IB_QPS_RESET;
	if (ib_modify_qp(priv->qp, &qp_attr, IB_QP_STATE))
		ipoib_warn(priv, "Failed to modify QP to RESET state\n");

	ib_req_notify_cq(priv->recv_cq, IB_CQ_NEXT_COMP);

	return 0;
}