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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/ * txf_stats; int /*<<< orphan*/ * rxf_stats; } ;
struct TYPE_8__ {TYPE_2__ hw_stats; TYPE_1__* hw_stats_kva; } ;
struct bfi_enet_stats_req {int /*<<< orphan*/  rx_enet_mask; int /*<<< orphan*/  tx_enet_mask; } ;
struct TYPE_7__ {int stats_get_busy; struct bfi_enet_stats_req stats_get; } ;
struct bna {TYPE_4__ stats; int /*<<< orphan*/  bnad; TYPE_3__ stats_mod; } ;
struct bfi_msgq_mhdr {int dummy; } ;
struct bfi_enet_stats_txf {int dummy; } ;
struct bfi_enet_stats_rxf {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rxf_stats; } ;

/* Variables and functions */
 int BFI_ENET_CFG_MAX ; 
 int BIT (int) ; 
 int /*<<< orphan*/  BNA_CB_SUCCESS ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_stats_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnad_cb_stats_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  bpc ; 
 int /*<<< orphan*/  fc_rx ; 
 int /*<<< orphan*/  fc_tx ; 
 int /*<<< orphan*/  mac ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rad ; 
 int /*<<< orphan*/  rlb ; 

__attribute__((used)) static void
bna_bfi_stats_get_rsp(struct bna *bna, struct bfi_msgq_mhdr *msghdr)
{
	struct bfi_enet_stats_req *stats_req = &bna->stats_mod.stats_get;
	u64 *stats_src;
	u64 *stats_dst;
	u32 tx_enet_mask = ntohl(stats_req->tx_enet_mask);
	u32 rx_enet_mask = ntohl(stats_req->rx_enet_mask);
	int count;
	int i;

	bna_stats_copy(mac, mac);
	bna_stats_copy(bpc, bpc);
	bna_stats_copy(rad, rad);
	bna_stats_copy(rlb, rad);
	bna_stats_copy(fc_rx, fc_rx);
	bna_stats_copy(fc_tx, fc_tx);

	stats_src = (u64 *)&(bna->stats.hw_stats_kva->rxf_stats[0]);

	/* Copy Rxf stats to SW area, scatter them while copying */
	for (i = 0; i < BFI_ENET_CFG_MAX; i++) {
		stats_dst = (u64 *)&(bna->stats.hw_stats.rxf_stats[i]);
		memset(stats_dst, 0, sizeof(struct bfi_enet_stats_rxf));
		if (rx_enet_mask & BIT(i)) {
			int k;
			count = sizeof(struct bfi_enet_stats_rxf) /
				sizeof(u64);
			for (k = 0; k < count; k++) {
				stats_dst[k] = be64_to_cpu(*stats_src);
				stats_src++;
			}
		}
	}

	/* Copy Txf stats to SW area, scatter them while copying */
	for (i = 0; i < BFI_ENET_CFG_MAX; i++) {
		stats_dst = (u64 *)&(bna->stats.hw_stats.txf_stats[i]);
		memset(stats_dst, 0, sizeof(struct bfi_enet_stats_txf));
		if (tx_enet_mask & BIT(i)) {
			int k;
			count = sizeof(struct bfi_enet_stats_txf) /
				sizeof(u64);
			for (k = 0; k < count; k++) {
				stats_dst[k] = be64_to_cpu(*stats_src);
				stats_src++;
			}
		}
	}

	bna->stats_mod.stats_get_busy = false;
	bnad_cb_stats_get(bna->bnad, BNA_CB_SUCCESS, &bna->stats);
}