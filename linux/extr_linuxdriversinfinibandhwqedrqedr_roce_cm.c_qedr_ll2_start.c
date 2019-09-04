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
struct qedr_qp {int dummy; } ;
struct qedr_dev {int /*<<< orphan*/  gsi_ll2_handle; int /*<<< orphan*/  rdma_ctx; TYPE_4__* ops; TYPE_3__* ndev; int /*<<< orphan*/  cdev; } ;
struct qed_ll2_cbs {struct qedr_dev* cookie; void* tx_release_cb; int /*<<< orphan*/  rx_release_cb; void* tx_comp_cb; int /*<<< orphan*/  rx_comp_cb; } ;
struct TYPE_6__ {int rx_drop_ttl0_flg; int rx_vlan_removal_en; int gsi_enable; void* ai_err_no_buf; void* ai_err_packet_too_big; int /*<<< orphan*/  tx_dest; scalar_t__ tx_tc; int /*<<< orphan*/  tx_num_desc; int /*<<< orphan*/  rx_num_desc; int /*<<< orphan*/  mtu; int /*<<< orphan*/  conn_type; } ;
struct qed_ll2_acquire_data {struct qed_ll2_cbs* cbs; int /*<<< orphan*/ * p_connection_handle; TYPE_2__ input; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {TYPE_1__ cap; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_8__ {int (* ll2_acquire_connection ) (int /*<<< orphan*/ ,struct qed_ll2_acquire_data*) ;int (* ll2_establish_connection ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int (* ll2_set_mac_filter ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ll2_release_connection ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ll2_terminate_connection ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qedr_dev*,char*,int) ; 
 void* QED_LL2_DROP_PACKET ; 
 int /*<<< orphan*/  QED_LL2_TX_DEST_NW ; 
 int /*<<< orphan*/  QED_LL2_TYPE_ROCE ; 
 int /*<<< orphan*/  memset (struct qed_ll2_acquire_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qedr_ll2_complete_rx_packet ; 
 void* qedr_ll2_complete_tx_packet ; 
 int /*<<< orphan*/  qedr_ll2_release_rx_packet ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_ll2_acquire_data*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedr_ll2_start(struct qedr_dev *dev,
			  struct ib_qp_init_attr *attrs, struct qedr_qp *qp)
{
	struct qed_ll2_acquire_data data;
	struct qed_ll2_cbs cbs;
	int rc;

	/* configure and start LL2 */
	cbs.rx_comp_cb = qedr_ll2_complete_rx_packet;
	cbs.tx_comp_cb = qedr_ll2_complete_tx_packet;
	cbs.rx_release_cb = qedr_ll2_release_rx_packet;
	cbs.tx_release_cb = qedr_ll2_complete_tx_packet;
	cbs.cookie = dev;

	memset(&data, 0, sizeof(data));
	data.input.conn_type = QED_LL2_TYPE_ROCE;
	data.input.mtu = dev->ndev->mtu;
	data.input.rx_num_desc = attrs->cap.max_recv_wr;
	data.input.rx_drop_ttl0_flg = true;
	data.input.rx_vlan_removal_en = false;
	data.input.tx_num_desc = attrs->cap.max_send_wr;
	data.input.tx_tc = 0;
	data.input.tx_dest = QED_LL2_TX_DEST_NW;
	data.input.ai_err_packet_too_big = QED_LL2_DROP_PACKET;
	data.input.ai_err_no_buf = QED_LL2_DROP_PACKET;
	data.input.gsi_enable = 1;
	data.p_connection_handle = &dev->gsi_ll2_handle;
	data.cbs = &cbs;

	rc = dev->ops->ll2_acquire_connection(dev->rdma_ctx, &data);
	if (rc) {
		DP_ERR(dev,
		       "ll2 start: failed to acquire LL2 connection (rc=%d)\n",
		       rc);
		return rc;
	}

	rc = dev->ops->ll2_establish_connection(dev->rdma_ctx,
						dev->gsi_ll2_handle);
	if (rc) {
		DP_ERR(dev,
		       "ll2 start: failed to establish LL2 connection (rc=%d)\n",
		       rc);
		goto err1;
	}

	rc = dev->ops->ll2_set_mac_filter(dev->cdev, NULL, dev->ndev->dev_addr);
	if (rc)
		goto err2;

	return 0;

err2:
	dev->ops->ll2_terminate_connection(dev->rdma_ctx, dev->gsi_ll2_handle);
err1:
	dev->ops->ll2_release_connection(dev->rdma_ctx, dev->gsi_ll2_handle);

	return rc;
}