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
typedef  int /*<<< orphan*/  u64 ;
struct aq_vec_s {int dummy; } ;
struct aq_ring_stats_tx_s {scalar_t__ errors; scalar_t__ lro_packets; scalar_t__ jumbo_packets; scalar_t__ queue_restarts; scalar_t__ packets; } ;
struct aq_ring_stats_rx_s {scalar_t__ errors; scalar_t__ lro_packets; scalar_t__ jumbo_packets; scalar_t__ queue_restarts; scalar_t__ packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  aq_vec_add_stats (struct aq_vec_s*,struct aq_ring_stats_tx_s*,struct aq_ring_stats_tx_s*) ; 
 int /*<<< orphan*/  memset (struct aq_ring_stats_tx_s*,unsigned int,int) ; 

int aq_vec_get_sw_stats(struct aq_vec_s *self, u64 *data, unsigned int *p_count)
{
	unsigned int count = 0U;
	struct aq_ring_stats_rx_s stats_rx;
	struct aq_ring_stats_tx_s stats_tx;

	memset(&stats_rx, 0U, sizeof(struct aq_ring_stats_rx_s));
	memset(&stats_tx, 0U, sizeof(struct aq_ring_stats_tx_s));
	aq_vec_add_stats(self, &stats_rx, &stats_tx);

	/* This data should mimic aq_ethtool_queue_stat_names structure
	 */
	data[count] += stats_rx.packets;
	data[++count] += stats_tx.packets;
	data[++count] += stats_tx.queue_restarts;
	data[++count] += stats_rx.jumbo_packets;
	data[++count] += stats_rx.lro_packets;
	data[++count] += stats_rx.errors;

	if (p_count)
		*p_count = ++count;

	return 0;
}