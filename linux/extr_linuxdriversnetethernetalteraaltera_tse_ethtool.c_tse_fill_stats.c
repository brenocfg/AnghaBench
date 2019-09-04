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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct altera_tse_private {int /*<<< orphan*/  mac_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  alignment_errors ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_stats_drop_events ; 
 int /*<<< orphan*/  ether_stats_fragments ; 
 int /*<<< orphan*/  ether_stats_jabbers ; 
 int /*<<< orphan*/  ether_stats_octets ; 
 int /*<<< orphan*/  ether_stats_oversize_pkts ; 
 int /*<<< orphan*/  ether_stats_pkts ; 
 int /*<<< orphan*/  ether_stats_pkts_1024to1518_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_128to255_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_1519tox_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_256to511_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_512to1023_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_64_octets ; 
 int /*<<< orphan*/  ether_stats_pkts_65to127_octets ; 
 int /*<<< orphan*/  ether_stats_undersize_pkts ; 
 int /*<<< orphan*/  frames_check_sequence_errors ; 
 int /*<<< orphan*/  frames_received_ok ; 
 int /*<<< orphan*/  frames_transmitted_ok ; 
 int /*<<< orphan*/  if_in_broadcast_pkts ; 
 int /*<<< orphan*/  if_in_errors ; 
 int /*<<< orphan*/  if_in_multicast_pkts ; 
 int /*<<< orphan*/  if_in_ucast_pkts ; 
 int /*<<< orphan*/  if_out_broadcast_pkts ; 
 int /*<<< orphan*/  if_out_discards ; 
 int /*<<< orphan*/  if_out_errors ; 
 int /*<<< orphan*/  if_out_multicast_pkts ; 
 int /*<<< orphan*/  if_out_ucast_pkts ; 
 int /*<<< orphan*/  msb_ether_stats_octets ; 
 int /*<<< orphan*/  msb_octets_received_ok ; 
 int /*<<< orphan*/  msb_octets_transmitted_ok ; 
 struct altera_tse_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  octets_received_ok ; 
 int /*<<< orphan*/  octets_transmitted_ok ; 
 int /*<<< orphan*/  rx_pause_mac_ctrl_frames ; 
 int /*<<< orphan*/  tse_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_pause_mac_ctrl_frames ; 

__attribute__((used)) static void tse_fill_stats(struct net_device *dev, struct ethtool_stats *dummy,
			   u64 *buf)
{
	struct altera_tse_private *priv = netdev_priv(dev);
	u64 ext;

	buf[0] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_transmitted_ok));
	buf[1] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_received_ok));
	buf[2] = csrrd32(priv->mac_dev,
			 tse_csroffs(frames_check_sequence_errors));
	buf[3] = csrrd32(priv->mac_dev,
			 tse_csroffs(alignment_errors));

	/* Extended aOctetsTransmittedOK counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_octets_transmitted_ok)) << 32;

	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(octets_transmitted_ok));
	buf[4] = ext;

	/* Extended aOctetsReceivedOK counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_octets_received_ok)) << 32;

	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(octets_received_ok));
	buf[5] = ext;

	buf[6] = csrrd32(priv->mac_dev,
			 tse_csroffs(tx_pause_mac_ctrl_frames));
	buf[7] = csrrd32(priv->mac_dev,
			 tse_csroffs(rx_pause_mac_ctrl_frames));
	buf[8] = csrrd32(priv->mac_dev,
			 tse_csroffs(if_in_errors));
	buf[9] = csrrd32(priv->mac_dev,
			 tse_csroffs(if_out_errors));
	buf[10] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_in_ucast_pkts));
	buf[11] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_in_multicast_pkts));
	buf[12] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_in_broadcast_pkts));
	buf[13] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_out_discards));
	buf[14] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_out_ucast_pkts));
	buf[15] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_out_multicast_pkts));
	buf[16] = csrrd32(priv->mac_dev,
			  tse_csroffs(if_out_broadcast_pkts));
	buf[17] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_drop_events));

	/* Extended etherStatsOctets counter */
	ext = (u64) csrrd32(priv->mac_dev,
			    tse_csroffs(msb_ether_stats_octets)) << 32;
	ext |= csrrd32(priv->mac_dev,
		       tse_csroffs(ether_stats_octets));
	buf[18] = ext;

	buf[19] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts));
	buf[20] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_undersize_pkts));
	buf[21] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_oversize_pkts));
	buf[22] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_64_octets));
	buf[23] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_65to127_octets));
	buf[24] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_128to255_octets));
	buf[25] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_256to511_octets));
	buf[26] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_512to1023_octets));
	buf[27] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_1024to1518_octets));
	buf[28] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_pkts_1519tox_octets));
	buf[29] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_jabbers));
	buf[30] = csrrd32(priv->mac_dev,
			  tse_csroffs(ether_stats_fragments));
}