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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {scalar_t__ small_pkt_cnt; scalar_t__ large_pkt_cnt; } ;
struct bna_ccb {TYPE_4__* cq; int /*<<< orphan*/  rx_coalescing_timeo; TYPE_2__ pkt_rate; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** dim_vector; } ;
struct bna {TYPE_3__ rx_mod; } ;
struct TYPE_8__ {int /*<<< orphan*/  ib; TYPE_1__* rx; } ;
struct TYPE_5__ {struct bna* bna; } ;

/* Variables and functions */
 scalar_t__ BNA_LOAD_T_HIGH_1 ; 
 scalar_t__ BNA_LOAD_T_HIGH_2 ; 
 scalar_t__ BNA_LOAD_T_HIGH_3 ; 
 scalar_t__ BNA_LOAD_T_HIGH_4 ; 
 scalar_t__ BNA_LOAD_T_LOW_1 ; 
 scalar_t__ BNA_LOAD_T_LOW_2 ; 
 scalar_t__ BNA_LOAD_T_LOW_3 ; 
 scalar_t__ BNA_LOAD_T_LOW_4 ; 
 scalar_t__ BNA_PKT_RATE_10K ; 
 scalar_t__ BNA_PKT_RATE_20K ; 
 scalar_t__ BNA_PKT_RATE_30K ; 
 scalar_t__ BNA_PKT_RATE_40K ; 
 scalar_t__ BNA_PKT_RATE_50K ; 
 scalar_t__ BNA_PKT_RATE_60K ; 
 scalar_t__ BNA_PKT_RATE_80K ; 
 int /*<<< orphan*/  bna_ib_coalescing_timeo_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
bna_rx_dim_update(struct bna_ccb *ccb)
{
	struct bna *bna = ccb->cq->rx->bna;
	u32 load, bias;
	u32 pkt_rt, small_rt, large_rt;
	u8 coalescing_timeo;

	if ((ccb->pkt_rate.small_pkt_cnt == 0) &&
		(ccb->pkt_rate.large_pkt_cnt == 0))
		return;

	/* Arrive at preconfigured coalescing timeo value based on pkt rate */

	small_rt = ccb->pkt_rate.small_pkt_cnt;
	large_rt = ccb->pkt_rate.large_pkt_cnt;

	pkt_rt = small_rt + large_rt;

	if (pkt_rt < BNA_PKT_RATE_10K)
		load = BNA_LOAD_T_LOW_4;
	else if (pkt_rt < BNA_PKT_RATE_20K)
		load = BNA_LOAD_T_LOW_3;
	else if (pkt_rt < BNA_PKT_RATE_30K)
		load = BNA_LOAD_T_LOW_2;
	else if (pkt_rt < BNA_PKT_RATE_40K)
		load = BNA_LOAD_T_LOW_1;
	else if (pkt_rt < BNA_PKT_RATE_50K)
		load = BNA_LOAD_T_HIGH_1;
	else if (pkt_rt < BNA_PKT_RATE_60K)
		load = BNA_LOAD_T_HIGH_2;
	else if (pkt_rt < BNA_PKT_RATE_80K)
		load = BNA_LOAD_T_HIGH_3;
	else
		load = BNA_LOAD_T_HIGH_4;

	if (small_rt > (large_rt << 1))
		bias = 0;
	else
		bias = 1;

	ccb->pkt_rate.small_pkt_cnt = 0;
	ccb->pkt_rate.large_pkt_cnt = 0;

	coalescing_timeo = bna->rx_mod.dim_vector[load][bias];
	ccb->rx_coalescing_timeo = coalescing_timeo;

	/* Set it to IB */
	bna_ib_coalescing_timeo_set(&ccb->cq->ib, coalescing_timeo);
}