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
struct net_device_stats {scalar_t__ tx_fifo_errors; scalar_t__ tx_carrier_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_crc_errors; scalar_t__ rx_over_errors; scalar_t__ rx_length_errors; scalar_t__ collisions; int /*<<< orphan*/  multicast; scalar_t__ tx_errors; scalar_t__ rx_errors; } ;
struct gem_stats {scalar_t__ tx_underrun; scalar_t__ tx_carrier_sense_errors; scalar_t__ tx_excessive_collisions; scalar_t__ rx_overruns; scalar_t__ rx_alignment_errors; scalar_t__ rx_frame_check_sequence_errors; scalar_t__ rx_resource_errors; scalar_t__ rx_length_field_frame_errors; scalar_t__ rx_undersized_frames; scalar_t__ rx_jabbers; scalar_t__ rx_oversize_frames; scalar_t__ tx_multiple_collision_frames; scalar_t__ tx_single_collision_frames; int /*<<< orphan*/  rx_multicast_frames; scalar_t__ tx_late_collisions; } ;
struct TYPE_3__ {struct gem_stats gem; } ;
struct macb {TYPE_2__* dev; TYPE_1__ hw_stats; } ;
struct TYPE_4__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  gem_update_stats (struct macb*) ; 

__attribute__((used)) static struct net_device_stats *gem_get_stats(struct macb *bp)
{
	struct gem_stats *hwstat = &bp->hw_stats.gem;
	struct net_device_stats *nstat = &bp->dev->stats;

	gem_update_stats(bp);

	nstat->rx_errors = (hwstat->rx_frame_check_sequence_errors +
			    hwstat->rx_alignment_errors +
			    hwstat->rx_resource_errors +
			    hwstat->rx_overruns +
			    hwstat->rx_oversize_frames +
			    hwstat->rx_jabbers +
			    hwstat->rx_undersized_frames +
			    hwstat->rx_length_field_frame_errors);
	nstat->tx_errors = (hwstat->tx_late_collisions +
			    hwstat->tx_excessive_collisions +
			    hwstat->tx_underrun +
			    hwstat->tx_carrier_sense_errors);
	nstat->multicast = hwstat->rx_multicast_frames;
	nstat->collisions = (hwstat->tx_single_collision_frames +
			     hwstat->tx_multiple_collision_frames +
			     hwstat->tx_excessive_collisions);
	nstat->rx_length_errors = (hwstat->rx_oversize_frames +
				   hwstat->rx_jabbers +
				   hwstat->rx_undersized_frames +
				   hwstat->rx_length_field_frame_errors);
	nstat->rx_over_errors = hwstat->rx_resource_errors;
	nstat->rx_crc_errors = hwstat->rx_frame_check_sequence_errors;
	nstat->rx_frame_errors = hwstat->rx_alignment_errors;
	nstat->rx_fifo_errors = hwstat->rx_overruns;
	nstat->tx_aborted_errors = hwstat->tx_excessive_collisions;
	nstat->tx_carrier_errors = hwstat->tx_carrier_sense_errors;
	nstat->tx_fifo_errors = hwstat->tx_underrun;

	return nstat;
}