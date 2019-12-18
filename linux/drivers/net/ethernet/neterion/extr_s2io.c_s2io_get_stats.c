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
typedef  int u64 ;
struct stat_block {int /*<<< orphan*/  rmac_fcs_err_frms; int /*<<< orphan*/  rmac_long_frms; int /*<<< orphan*/  rmac_usized_frms; int /*<<< orphan*/  rmac_usized_frms_oflow; int /*<<< orphan*/  rmac_pause_ctrl_frms; int /*<<< orphan*/  rmac_vld_mcst_frms; int /*<<< orphan*/  rmac_vld_mcst_frms_oflow; int /*<<< orphan*/  tmac_drop_frms; int /*<<< orphan*/  rmac_drop_frms; int /*<<< orphan*/  tmac_any_err_frms; int /*<<< orphan*/  tmac_any_err_frms_oflow; int /*<<< orphan*/  tmac_data_octets; int /*<<< orphan*/  tmac_data_octets_oflow; int /*<<< orphan*/  rmac_data_octets; int /*<<< orphan*/  rmac_data_octets_oflow; int /*<<< orphan*/  tmac_frms; int /*<<< orphan*/  tmac_frms_oflow; int /*<<< orphan*/  rmac_vld_frms; int /*<<< orphan*/  rmac_vld_frms_oflow; } ;
struct TYPE_2__ {int rx_packets; int tx_packets; int rx_bytes; int tx_bytes; int rx_errors; int tx_errors; int rx_dropped; int tx_dropped; int rx_length_errors; int rx_crc_errors; scalar_t__ multicast; } ;
struct mac_info {struct stat_block* stats_info; } ;
struct s2io_nic {TYPE_1__ stats; struct mac_info mac_control; } ;
struct net_device_stats {int rx_packets; int tx_packets; int rx_bytes; int tx_bytes; int rx_errors; int tx_errors; int rx_dropped; int tx_dropped; int multicast; int rx_length_errors; int rx_crc_errors; } ;
struct net_device {struct net_device_stats stats; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s2io_updt_stats (struct s2io_nic*) ; 

__attribute__((used)) static struct net_device_stats *s2io_get_stats(struct net_device *dev)
{
	struct s2io_nic *sp = netdev_priv(dev);
	struct mac_info *mac_control = &sp->mac_control;
	struct stat_block *stats = mac_control->stats_info;
	u64 delta;

	/* Configure Stats for immediate updt */
	s2io_updt_stats(sp);

	/* A device reset will cause the on-adapter statistics to be zero'ed.
	 * This can be done while running by changing the MTU.  To prevent the
	 * system from having the stats zero'ed, the driver keeps a copy of the
	 * last update to the system (which is also zero'ed on reset).  This
	 * enables the driver to accurately know the delta between the last
	 * update and the current update.
	 */
	delta = ((u64) le32_to_cpu(stats->rmac_vld_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_frms)) - sp->stats.rx_packets;
	sp->stats.rx_packets += delta;
	dev->stats.rx_packets += delta;

	delta = ((u64) le32_to_cpu(stats->tmac_frms_oflow) << 32 |
		le32_to_cpu(stats->tmac_frms)) - sp->stats.tx_packets;
	sp->stats.tx_packets += delta;
	dev->stats.tx_packets += delta;

	delta = ((u64) le32_to_cpu(stats->rmac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->rmac_data_octets)) - sp->stats.rx_bytes;
	sp->stats.rx_bytes += delta;
	dev->stats.rx_bytes += delta;

	delta = ((u64) le32_to_cpu(stats->tmac_data_octets_oflow) << 32 |
		le32_to_cpu(stats->tmac_data_octets)) - sp->stats.tx_bytes;
	sp->stats.tx_bytes += delta;
	dev->stats.tx_bytes += delta;

	delta = le64_to_cpu(stats->rmac_drop_frms) - sp->stats.rx_errors;
	sp->stats.rx_errors += delta;
	dev->stats.rx_errors += delta;

	delta = ((u64) le32_to_cpu(stats->tmac_any_err_frms_oflow) << 32 |
		le32_to_cpu(stats->tmac_any_err_frms)) - sp->stats.tx_errors;
	sp->stats.tx_errors += delta;
	dev->stats.tx_errors += delta;

	delta = le64_to_cpu(stats->rmac_drop_frms) - sp->stats.rx_dropped;
	sp->stats.rx_dropped += delta;
	dev->stats.rx_dropped += delta;

	delta = le64_to_cpu(stats->tmac_drop_frms) - sp->stats.tx_dropped;
	sp->stats.tx_dropped += delta;
	dev->stats.tx_dropped += delta;

	/* The adapter MAC interprets pause frames as multicast packets, but
	 * does not pass them up.  This erroneously increases the multicast
	 * packet count and needs to be deducted when the multicast frame count
	 * is queried.
	 */
	delta = (u64) le32_to_cpu(stats->rmac_vld_mcst_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_vld_mcst_frms);
	delta -= le64_to_cpu(stats->rmac_pause_ctrl_frms);
	delta -= sp->stats.multicast;
	sp->stats.multicast += delta;
	dev->stats.multicast += delta;

	delta = ((u64) le32_to_cpu(stats->rmac_usized_frms_oflow) << 32 |
		le32_to_cpu(stats->rmac_usized_frms)) +
		le64_to_cpu(stats->rmac_long_frms) - sp->stats.rx_length_errors;
	sp->stats.rx_length_errors += delta;
	dev->stats.rx_length_errors += delta;

	delta = le64_to_cpu(stats->rmac_fcs_err_frms) - sp->stats.rx_crc_errors;
	sp->stats.rx_crc_errors += delta;
	dev->stats.rx_crc_errors += delta;

	return &dev->stats;
}