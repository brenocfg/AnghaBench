#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_3__ {scalar_t__ state; } ;
struct ti_hecc_priv {int /*<<< orphan*/  offload; int /*<<< orphan*/  ndev; TYPE_1__ can; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_fifo_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct can_frame {void** data; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 scalar_t__ CAN_STATE_BUS_OFF ; 
 int /*<<< orphan*/  HECC_CANLNT ; 
 int /*<<< orphan*/  HECC_CANREC ; 
 int /*<<< orphan*/  HECC_CANTEC ; 
 struct sk_buff* alloc_can_err_skb (int /*<<< orphan*/ ,struct can_frame**) ; 
 int /*<<< orphan*/  can_change_state (int /*<<< orphan*/ ,struct can_frame*,int,int) ; 
 int can_rx_offload_queue_sorted (int /*<<< orphan*/ *,struct sk_buff*,void*) ; 
 void* hecc_read (struct ti_hecc_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ max (int,int) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ti_hecc_change_state(struct net_device *ndev,
				 enum can_state rx_state,
				 enum can_state tx_state)
{
	struct ti_hecc_priv *priv = netdev_priv(ndev);
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 timestamp;
	int err;

	skb = alloc_can_err_skb(priv->ndev, &cf);
	if (unlikely(!skb)) {
		priv->can.state = max(tx_state, rx_state);
		return;
	}

	can_change_state(priv->ndev, cf, tx_state, rx_state);

	if (max(tx_state, rx_state) != CAN_STATE_BUS_OFF) {
		cf->data[6] = hecc_read(priv, HECC_CANTEC);
		cf->data[7] = hecc_read(priv, HECC_CANREC);
	}

	timestamp = hecc_read(priv, HECC_CANLNT);
	err = can_rx_offload_queue_sorted(&priv->offload, skb, timestamp);
	if (err)
		ndev->stats.rx_fifo_errors++;
}