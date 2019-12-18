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
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct sja1105_private {TYPE_1__ tagger_data; TYPE_2__* ports; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; scalar_t__ flags; } ;
struct dsa_switch {struct sja1105_private* priv; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_4__ {scalar_t__ hwts_tx_en; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_PTP_V2_L2_EVENT ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  HWTSTAMP_TX_ON ; 
 int /*<<< orphan*/  SJA1105_HWTS_RX_EN ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sja1105_hwtstamp_get(struct dsa_switch *ds, int port,
				struct ifreq *ifr)
{
	struct sja1105_private *priv = ds->priv;
	struct hwtstamp_config config;

	config.flags = 0;
	if (priv->ports[port].hwts_tx_en)
		config.tx_type = HWTSTAMP_TX_ON;
	else
		config.tx_type = HWTSTAMP_TX_OFF;
	if (test_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state))
		config.rx_filter = HWTSTAMP_FILTER_PTP_V2_L2_EVENT;
	else
		config.rx_filter = HWTSTAMP_FILTER_NONE;

	return copy_to_user(ifr->ifr_data, &config, sizeof(config)) ?
		-EFAULT : 0;
}