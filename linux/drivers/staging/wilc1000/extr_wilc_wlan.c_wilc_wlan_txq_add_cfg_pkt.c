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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {int /*<<< orphan*/  ndev; struct wilc* wilc; } ;
struct wilc {int /*<<< orphan*/  cfg_event; scalar_t__ quit; } ;
struct txq_entry_t {struct wilc_vif* vif; int /*<<< orphan*/  ack_idx; int /*<<< orphan*/ * priv; int /*<<< orphan*/ * tx_complete_func; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NOT_TCP_ACK ; 
 int /*<<< orphan*/  WILC_CFG_PKT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct txq_entry_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wilc_wlan_txq_add_to_head (struct wilc_vif*,struct txq_entry_t*) ; 

__attribute__((used)) static int wilc_wlan_txq_add_cfg_pkt(struct wilc_vif *vif, u8 *buffer,
				     u32 buffer_size)
{
	struct txq_entry_t *tqe;
	struct wilc *wilc = vif->wilc;

	netdev_dbg(vif->ndev, "Adding config packet ...\n");
	if (wilc->quit) {
		netdev_dbg(vif->ndev, "Return due to clear function\n");
		complete(&wilc->cfg_event);
		return 0;
	}

	tqe = kmalloc(sizeof(*tqe), GFP_ATOMIC);
	if (!tqe)
		return 0;

	tqe->type = WILC_CFG_PKT;
	tqe->buffer = buffer;
	tqe->buffer_size = buffer_size;
	tqe->tx_complete_func = NULL;
	tqe->priv = NULL;
	tqe->ack_idx = NOT_TCP_ACK;
	tqe->vif = vif;

	wilc_wlan_txq_add_to_head(vif, tqe);

	return 1;
}