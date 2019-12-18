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
typedef  int /*<<< orphan*/  tally ;
struct tally_counter {int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  tx_multi_collision; int /*<<< orphan*/  tx_one_collision; int /*<<< orphan*/  align_errors; int /*<<< orphan*/  rx_missed; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_packets; } ;
struct r8152 {int /*<<< orphan*/  intf; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  PLA_TALLYCNT ; 
 int /*<<< orphan*/  generic_ocp_read (struct r8152*,int /*<<< orphan*/ ,int,struct tally_counter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct r8152* netdev_priv (struct net_device*) ; 
 scalar_t__ usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8152_get_ethtool_stats(struct net_device *dev,
				      struct ethtool_stats *stats, u64 *data)
{
	struct r8152 *tp = netdev_priv(dev);
	struct tally_counter tally;

	if (usb_autopm_get_interface(tp->intf) < 0)
		return;

	generic_ocp_read(tp, PLA_TALLYCNT, sizeof(tally), &tally, MCU_TYPE_PLA);

	usb_autopm_put_interface(tp->intf);

	data[0] = le64_to_cpu(tally.tx_packets);
	data[1] = le64_to_cpu(tally.rx_packets);
	data[2] = le64_to_cpu(tally.tx_errors);
	data[3] = le32_to_cpu(tally.rx_errors);
	data[4] = le16_to_cpu(tally.rx_missed);
	data[5] = le16_to_cpu(tally.align_errors);
	data[6] = le32_to_cpu(tally.tx_one_collision);
	data[7] = le32_to_cpu(tally.tx_multi_collision);
	data[8] = le64_to_cpu(tally.rx_unicast);
	data[9] = le64_to_cpu(tally.rx_broadcast);
	data[10] = le32_to_cpu(tally.rx_multicast);
	data[11] = le16_to_cpu(tally.tx_aborted);
	data[12] = le16_to_cpu(tally.tx_underrun);
}