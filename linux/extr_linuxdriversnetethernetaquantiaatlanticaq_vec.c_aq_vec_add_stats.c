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
struct aq_vec_s {unsigned int tx_rings; struct aq_ring_s** ring; } ;
struct aq_ring_stats_tx_s {scalar_t__ queue_restarts; scalar_t__ errors; scalar_t__ bytes; scalar_t__ packets; } ;
struct aq_ring_stats_rx_s {scalar_t__ lro_packets; scalar_t__ jumbo_packets; scalar_t__ errors; scalar_t__ bytes; scalar_t__ packets; } ;
struct TYPE_2__ {struct aq_ring_stats_rx_s rx; struct aq_ring_stats_tx_s tx; } ;
struct aq_ring_s {TYPE_1__ stats; } ;

/* Variables and functions */
 size_t AQ_VEC_RX_ID ; 
 size_t AQ_VEC_TX_ID ; 

void aq_vec_add_stats(struct aq_vec_s *self,
		      struct aq_ring_stats_rx_s *stats_rx,
		      struct aq_ring_stats_tx_s *stats_tx)
{
	struct aq_ring_s *ring = NULL;
	unsigned int r = 0U;

	for (r = 0U, ring = self->ring[0];
		self->tx_rings > r; ++r, ring = self->ring[r]) {
		struct aq_ring_stats_tx_s *tx = &ring[AQ_VEC_TX_ID].stats.tx;
		struct aq_ring_stats_rx_s *rx = &ring[AQ_VEC_RX_ID].stats.rx;

		stats_rx->packets += rx->packets;
		stats_rx->bytes += rx->bytes;
		stats_rx->errors += rx->errors;
		stats_rx->jumbo_packets += rx->jumbo_packets;
		stats_rx->lro_packets += rx->lro_packets;

		stats_tx->packets += tx->packets;
		stats_tx->bytes += tx->bytes;
		stats_tx->errors += tx->errors;
		stats_tx->queue_restarts += tx->queue_restarts;
	}
}