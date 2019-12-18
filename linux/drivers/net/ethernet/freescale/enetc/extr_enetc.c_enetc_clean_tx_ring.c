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
union enetc_tx_bd {int flags; } ;
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct enetc_tx_swbd {int check_wb; scalar_t__ len; int /*<<< orphan*/ * skb; int /*<<< orphan*/  dma; scalar_t__ do_tstamp; } ;
struct enetc_ndev_priv {TYPE_1__* si; } ;
struct TYPE_4__ {int packets; int bytes; } ;
struct enetc_bdr {int next_to_clean; int bd_count; int /*<<< orphan*/  index; TYPE_2__ stats; int /*<<< orphan*/  idr; struct enetc_tx_swbd* tx_swbd; struct net_device* ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENETC_DEFAULT_TX_WORK ; 
 union enetc_tx_bd* ENETC_TXBD (struct enetc_bdr,int) ; 
 scalar_t__ ENETC_TXBDS_MAX_NEEDED ; 
 int ENETC_TXBD_FLAGS_W ; 
 scalar_t__ __netif_subqueue_stopped (struct net_device*,int /*<<< orphan*/ ) ; 
 int enetc_bd_ready_count (struct enetc_bdr*,int) ; 
 scalar_t__ enetc_bd_unused (struct enetc_bdr*) ; 
 int /*<<< orphan*/  enetc_get_tx_tstamp (int /*<<< orphan*/ *,union enetc_tx_bd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enetc_tstamp_tx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_unmap_tx_buff (struct enetc_bdr*,struct enetc_tx_swbd*) ; 
 int /*<<< orphan*/  enetc_wr_reg (int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ *,int) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_subqueue (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool enetc_clean_tx_ring(struct enetc_bdr *tx_ring, int napi_budget)
{
	struct net_device *ndev = tx_ring->ndev;
	int tx_frm_cnt = 0, tx_byte_cnt = 0;
	struct enetc_tx_swbd *tx_swbd;
	int i, bds_to_clean;
	bool do_tstamp;
	u64 tstamp = 0;

	i = tx_ring->next_to_clean;
	tx_swbd = &tx_ring->tx_swbd[i];
	bds_to_clean = enetc_bd_ready_count(tx_ring, i);

	do_tstamp = false;

	while (bds_to_clean && tx_frm_cnt < ENETC_DEFAULT_TX_WORK) {
		bool is_eof = !!tx_swbd->skb;

		if (unlikely(tx_swbd->check_wb)) {
			struct enetc_ndev_priv *priv = netdev_priv(ndev);
			union enetc_tx_bd *txbd;

			txbd = ENETC_TXBD(*tx_ring, i);

			if (txbd->flags & ENETC_TXBD_FLAGS_W &&
			    tx_swbd->do_tstamp) {
				enetc_get_tx_tstamp(&priv->si->hw, txbd,
						    &tstamp);
				do_tstamp = true;
			}
		}

		if (likely(tx_swbd->dma))
			enetc_unmap_tx_buff(tx_ring, tx_swbd);

		if (is_eof) {
			if (unlikely(do_tstamp)) {
				enetc_tstamp_tx(tx_swbd->skb, tstamp);
				do_tstamp = false;
			}
			napi_consume_skb(tx_swbd->skb, napi_budget);
			tx_swbd->skb = NULL;
		}

		tx_byte_cnt += tx_swbd->len;

		bds_to_clean--;
		tx_swbd++;
		i++;
		if (unlikely(i == tx_ring->bd_count)) {
			i = 0;
			tx_swbd = tx_ring->tx_swbd;
		}

		/* BD iteration loop end */
		if (is_eof) {
			tx_frm_cnt++;
			/* re-arm interrupt source */
			enetc_wr_reg(tx_ring->idr, BIT(tx_ring->index) |
				     BIT(16 + tx_ring->index));
		}

		if (unlikely(!bds_to_clean))
			bds_to_clean = enetc_bd_ready_count(tx_ring, i);
	}

	tx_ring->next_to_clean = i;
	tx_ring->stats.packets += tx_frm_cnt;
	tx_ring->stats.bytes += tx_byte_cnt;

	if (unlikely(tx_frm_cnt && netif_carrier_ok(ndev) &&
		     __netif_subqueue_stopped(ndev, tx_ring->index) &&
		     (enetc_bd_unused(tx_ring) >= ENETC_TXBDS_MAX_NEEDED))) {
		netif_wake_subqueue(ndev, tx_ring->index);
	}

	return tx_frm_cnt != ENETC_DEFAULT_TX_WORK;
}