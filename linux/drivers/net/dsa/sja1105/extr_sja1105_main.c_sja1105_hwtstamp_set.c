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
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct sja1105_private {TYPE_2__ tagger_data; TYPE_1__* ports; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_3__ {int hwts_tx_en; } ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_NONE 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 int /*<<< orphan*/  SJA1105_HWTS_RX_EN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sja1105_change_rxtstamping (struct sja1105_private*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sja1105_hwtstamp_set(struct dsa_switch *ds, int port,
				struct ifreq *ifr)
{
	struct sja1105_private *priv = ds->priv;
	struct hwtstamp_config config;
	bool rx_on;
	int rc;

	if (copy_from_user(&config, ifr->ifr_data, sizeof(config)))
		return -EFAULT;

	switch (config.tx_type) {
	case HWTSTAMP_TX_OFF:
		priv->ports[port].hwts_tx_en = false;
		break;
	case HWTSTAMP_TX_ON:
		priv->ports[port].hwts_tx_en = true;
		break;
	default:
		return -ERANGE;
	}

	switch (config.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		rx_on = false;
		break;
	default:
		rx_on = true;
		break;
	}

	if (rx_on != test_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state)) {
		clear_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state);

		rc = sja1105_change_rxtstamping(priv, rx_on);
		if (rc < 0) {
			dev_err(ds->dev,
				"Failed to change RX timestamping: %d\n", rc);
			return rc;
		}
		if (rx_on)
			set_bit(SJA1105_HWTS_RX_EN, &priv->tagger_data.state);
	}

	if (copy_to_user(ifr->ifr_data, &config, sizeof(config)))
		return -EFAULT;
	return 0;
}