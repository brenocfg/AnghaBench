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
struct net_device {int dummy; } ;
struct ipoib_neigh {int /*<<< orphan*/ * cm; } ;
struct TYPE_2__ {int /*<<< orphan*/  reap_task; int /*<<< orphan*/  reap_list; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; TYPE_1__ cm; int /*<<< orphan*/  wq; struct net_device* dev; } ;
struct ipoib_cm_tx {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; struct ipoib_neigh* neigh; int /*<<< orphan*/  dev; } ;
struct ib_cm_id {struct ipoib_cm_tx* context; } ;
struct ib_cm_event {int event; } ;

/* Variables and functions */
#define  IB_CM_DREQ_RECEIVED 132 
 int /*<<< orphan*/  IB_CM_REJ_CONSUMER_DEFINED ; 
#define  IB_CM_REJ_RECEIVED 131 
#define  IB_CM_REP_RECEIVED 130 
#define  IB_CM_REQ_ERROR 129 
#define  IB_CM_TIMEWAIT_EXIT 128 
 int /*<<< orphan*/  IPOIB_FLAG_INITIALIZED ; 
 int /*<<< orphan*/  ib_send_cm_drep (struct ib_cm_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_send_cm_rej (struct ib_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ipoib_cm_rep_handler (struct ib_cm_id*,struct ib_cm_event const*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,...) ; 
 int /*<<< orphan*/  ipoib_neigh_free (struct ipoib_neigh*) ; 
 struct ipoib_dev_priv* ipoib_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_cm_tx_handler(struct ib_cm_id *cm_id,
			       const struct ib_cm_event *event)
{
	struct ipoib_cm_tx *tx = cm_id->context;
	struct ipoib_dev_priv *priv = ipoib_priv(tx->dev);
	struct net_device *dev = priv->dev;
	struct ipoib_neigh *neigh;
	unsigned long flags;
	int ret;

	switch (event->event) {
	case IB_CM_DREQ_RECEIVED:
		ipoib_dbg(priv, "DREQ received.\n");
		ib_send_cm_drep(cm_id, NULL, 0);
		break;
	case IB_CM_REP_RECEIVED:
		ipoib_dbg(priv, "REP received.\n");
		ret = ipoib_cm_rep_handler(cm_id, event);
		if (ret)
			ib_send_cm_rej(cm_id, IB_CM_REJ_CONSUMER_DEFINED,
				       NULL, 0, NULL, 0);
		break;
	case IB_CM_REQ_ERROR:
	case IB_CM_REJ_RECEIVED:
	case IB_CM_TIMEWAIT_EXIT:
		ipoib_dbg(priv, "CM error %d.\n", event->event);
		netif_tx_lock_bh(dev);
		spin_lock_irqsave(&priv->lock, flags);
		neigh = tx->neigh;

		if (neigh) {
			neigh->cm = NULL;
			ipoib_neigh_free(neigh);

			tx->neigh = NULL;
		}

		if (test_and_clear_bit(IPOIB_FLAG_INITIALIZED, &tx->flags)) {
			list_move(&tx->list, &priv->cm.reap_list);
			queue_work(priv->wq, &priv->cm.reap_task);
		}

		spin_unlock_irqrestore(&priv->lock, flags);
		netif_tx_unlock_bh(dev);
		break;
	default:
		break;
	}

	return 0;
}