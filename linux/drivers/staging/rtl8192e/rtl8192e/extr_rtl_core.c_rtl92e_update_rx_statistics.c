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
struct rtllib_rx_stats {int RecvSignalPower; } ;
struct TYPE_2__ {int recv_signal_power; } ;
struct r8192_priv {TYPE_1__ stats; } ;

/* Variables and functions */

void rtl92e_update_rx_statistics(struct r8192_priv *priv,
				 struct rtllib_rx_stats *pprevious_stats)
{
	int weighting = 0;


	if (priv->stats.recv_signal_power == 0)
		priv->stats.recv_signal_power =
					 pprevious_stats->RecvSignalPower;

	if (pprevious_stats->RecvSignalPower > priv->stats.recv_signal_power)
		weighting = 5;
	else if (pprevious_stats->RecvSignalPower <
		 priv->stats.recv_signal_power)
		weighting = (-5);
	priv->stats.recv_signal_power = (priv->stats.recv_signal_power * 5 +
					pprevious_stats->RecvSignalPower +
					weighting) / 6;
}