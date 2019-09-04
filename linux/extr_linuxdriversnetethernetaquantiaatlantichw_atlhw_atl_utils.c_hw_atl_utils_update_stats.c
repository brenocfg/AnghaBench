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
struct TYPE_8__ {scalar_t__ dpc; scalar_t__ bbtc; scalar_t__ bbrc; scalar_t__ mbtc; scalar_t__ mbrc; scalar_t__ ubtc; scalar_t__ ubrc; scalar_t__ erpr; scalar_t__ bptc; scalar_t__ mptc; scalar_t__ uptc; scalar_t__ erpt; scalar_t__ bprc; scalar_t__ mprc; scalar_t__ uprc; } ;
struct hw_aq_atl_utils_mbox {TYPE_4__ stats; } ;
struct TYPE_7__ {scalar_t__ dpc; scalar_t__ bbtc; scalar_t__ bbrc; scalar_t__ mbtc; scalar_t__ mbrc; scalar_t__ ubtc; scalar_t__ ubrc; scalar_t__ erpr; scalar_t__ bptc; scalar_t__ mptc; scalar_t__ uptc; scalar_t__ erpt; scalar_t__ bprc; scalar_t__ mprc; scalar_t__ uprc; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma_oct_tc; int /*<<< orphan*/  dma_oct_rc; int /*<<< orphan*/  dma_pkt_tc; int /*<<< orphan*/  dma_pkt_rc; int /*<<< orphan*/  dpc; int /*<<< orphan*/  bbtc; int /*<<< orphan*/  bbrc; int /*<<< orphan*/  mbtc; int /*<<< orphan*/  mbrc; int /*<<< orphan*/  ubtc; int /*<<< orphan*/  ubrc; int /*<<< orphan*/  erpr; int /*<<< orphan*/  bptc; int /*<<< orphan*/  mptc; int /*<<< orphan*/  uptc; int /*<<< orphan*/  erpt; int /*<<< orphan*/  bprc; int /*<<< orphan*/  mprc; int /*<<< orphan*/  uprc; } ;
struct TYPE_5__ {scalar_t__ mbps; } ;
struct aq_hw_s {TYPE_3__ last_stats; TYPE_2__ curr_stats; TYPE_1__ aq_link_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_atl_stats_rx_dma_good_octet_counterlsw_get (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_stats_rx_dma_good_pkt_counterlsw_get (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_stats_tx_dma_good_octet_counterlsw_get (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_stats_tx_dma_good_pkt_counterlsw_get (struct aq_hw_s*) ; 
 int /*<<< orphan*/  hw_atl_utils_mpi_read_stats (struct aq_hw_s*,struct hw_aq_atl_utils_mbox*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_4__*,int) ; 

int hw_atl_utils_update_stats(struct aq_hw_s *self)
{
	struct hw_aq_atl_utils_mbox mbox;

	hw_atl_utils_mpi_read_stats(self, &mbox);

#define AQ_SDELTA(_N_) (self->curr_stats._N_ += \
			mbox.stats._N_ - self->last_stats._N_)

	if (self->aq_link_status.mbps) {
		AQ_SDELTA(uprc);
		AQ_SDELTA(mprc);
		AQ_SDELTA(bprc);
		AQ_SDELTA(erpt);

		AQ_SDELTA(uptc);
		AQ_SDELTA(mptc);
		AQ_SDELTA(bptc);
		AQ_SDELTA(erpr);

		AQ_SDELTA(ubrc);
		AQ_SDELTA(ubtc);
		AQ_SDELTA(mbrc);
		AQ_SDELTA(mbtc);
		AQ_SDELTA(bbrc);
		AQ_SDELTA(bbtc);
		AQ_SDELTA(dpc);
	}
#undef AQ_SDELTA
	self->curr_stats.dma_pkt_rc = hw_atl_stats_rx_dma_good_pkt_counterlsw_get(self);
	self->curr_stats.dma_pkt_tc = hw_atl_stats_tx_dma_good_pkt_counterlsw_get(self);
	self->curr_stats.dma_oct_rc = hw_atl_stats_rx_dma_good_octet_counterlsw_get(self);
	self->curr_stats.dma_oct_tc = hw_atl_stats_tx_dma_good_octet_counterlsw_get(self);

	memcpy(&self->last_stats, &mbox.stats, sizeof(mbox.stats));

	return 0;
}