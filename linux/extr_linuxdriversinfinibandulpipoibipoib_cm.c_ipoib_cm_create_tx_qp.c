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
struct net_device {int features; } ;
struct TYPE_5__ {int /*<<< orphan*/  srq; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  pd; TYPE_3__* ca; TYPE_1__ cm; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct ipoib_cm_tx {int max_send_sge; } ;
struct TYPE_8__ {int max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {TYPE_4__ cap; int /*<<< orphan*/  create_flags; struct ipoib_cm_tx* qp_context; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct ib_qp {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_send_sge; } ;
struct TYPE_7__ {TYPE_2__ attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int NETIF_F_SG ; 
 struct ib_qp* ib_create_qp (int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_sendq_size ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static struct ib_qp *ipoib_cm_create_tx_qp(struct net_device *dev, struct ipoib_cm_tx *tx)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ib_qp_init_attr attr = {
		.send_cq		= priv->send_cq,
		.recv_cq		= priv->recv_cq,
		.srq			= priv->cm.srq,
		.cap.max_send_wr	= ipoib_sendq_size,
		.cap.max_send_sge	= 1,
		.sq_sig_type		= IB_SIGNAL_ALL_WR,
		.qp_type		= IB_QPT_RC,
		.qp_context		= tx,
		.create_flags		= 0
	};
	struct ib_qp *tx_qp;

	if (dev->features & NETIF_F_SG)
		attr.cap.max_send_sge = min_t(u32, priv->ca->attrs.max_send_sge,
					      MAX_SKB_FRAGS + 1);

	tx_qp = ib_create_qp(priv->pd, &attr);
	tx->max_send_sge = attr.cap.max_send_sge;
	return tx_qp;
}