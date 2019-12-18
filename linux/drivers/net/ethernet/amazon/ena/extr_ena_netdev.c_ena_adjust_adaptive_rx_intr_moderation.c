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
struct TYPE_2__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  cnt; } ;
struct ena_ring {scalar_t__ per_napi_packets; TYPE_1__ rx_stats; int /*<<< orphan*/  non_empty_napi_events; } ;
struct ena_napi {int /*<<< orphan*/  dim; struct ena_ring* rx_ring; } ;
struct dim_sample {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dim_update_sample (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dim_sample*) ; 
 int /*<<< orphan*/  net_dim (int /*<<< orphan*/ *,struct dim_sample) ; 

__attribute__((used)) static void ena_adjust_adaptive_rx_intr_moderation(struct ena_napi *ena_napi)
{
	struct dim_sample dim_sample;
	struct ena_ring *rx_ring = ena_napi->rx_ring;

	if (!rx_ring->per_napi_packets)
		return;

	rx_ring->non_empty_napi_events++;

	dim_update_sample(rx_ring->non_empty_napi_events,
			  rx_ring->rx_stats.cnt,
			  rx_ring->rx_stats.bytes,
			  &dim_sample);

	net_dim(&ena_napi->dim, dim_sample);

	rx_ring->per_napi_packets = 0;
}