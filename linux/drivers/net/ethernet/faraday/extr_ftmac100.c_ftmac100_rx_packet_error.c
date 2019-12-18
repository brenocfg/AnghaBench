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
struct TYPE_2__ {int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100 {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftmac100_rxdes_crc_error (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_frame_too_long (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_odd_nibble (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_runt (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_rx_error (struct ftmac100_rxdes*) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ftmac100_rx_packet_error(struct ftmac100 *priv,
				     struct ftmac100_rxdes *rxdes)
{
	struct net_device *netdev = priv->netdev;
	bool error = false;

	if (unlikely(ftmac100_rxdes_rx_error(rxdes))) {
		if (net_ratelimit())
			netdev_info(netdev, "rx err\n");

		netdev->stats.rx_errors++;
		error = true;
	}

	if (unlikely(ftmac100_rxdes_crc_error(rxdes))) {
		if (net_ratelimit())
			netdev_info(netdev, "rx crc err\n");

		netdev->stats.rx_crc_errors++;
		error = true;
	}

	if (unlikely(ftmac100_rxdes_frame_too_long(rxdes))) {
		if (net_ratelimit())
			netdev_info(netdev, "rx frame too long\n");

		netdev->stats.rx_length_errors++;
		error = true;
	} else if (unlikely(ftmac100_rxdes_runt(rxdes))) {
		if (net_ratelimit())
			netdev_info(netdev, "rx runt\n");

		netdev->stats.rx_length_errors++;
		error = true;
	} else if (unlikely(ftmac100_rxdes_odd_nibble(rxdes))) {
		if (net_ratelimit())
			netdev_info(netdev, "rx odd nibble\n");

		netdev->stats.rx_length_errors++;
		error = true;
	}

	return error;
}