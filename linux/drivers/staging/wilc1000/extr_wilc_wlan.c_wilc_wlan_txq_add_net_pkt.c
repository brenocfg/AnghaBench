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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct wilc_vif {TYPE_1__ ack_filter; struct wilc* wilc; } ;
struct wilc {int txq_entries; scalar_t__ quit; } ;
struct txq_entry_t {void (* tx_complete_func ) (void*,int) ;int /*<<< orphan*/  ack_idx; struct wilc_vif* vif; void* priv; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NOT_TCP_ACK ; 
 int /*<<< orphan*/  WILC_NET_PKT ; 
 struct txq_entry_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tcp_process (struct net_device*,struct txq_entry_t*) ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_to_tail (struct net_device*,struct txq_entry_t*) ; 

int wilc_wlan_txq_add_net_pkt(struct net_device *dev, void *priv, u8 *buffer,
			      u32 buffer_size,
			      void (*tx_complete_fn)(void *, int))
{
	struct txq_entry_t *tqe;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc;

	wilc = vif->wilc;

	if (wilc->quit)
		return 0;

	tqe = kmalloc(sizeof(*tqe), GFP_ATOMIC);

	if (!tqe)
		return 0;
	tqe->type = WILC_NET_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = tx_complete_fn;
	tqe->priv = priv;
	tqe->vif = vif;

	tqe->ack_idx = NOT_TCP_ACK;
	if (vif->ack_filter.enabled)
		tcp_process(dev, tqe);
	wilc_wlan_txq_add_to_tail(dev, tqe);
	return wilc->txq_entries;
}