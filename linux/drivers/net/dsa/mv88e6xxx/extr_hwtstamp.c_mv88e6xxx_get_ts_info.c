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
struct mv88e6xxx_ptp_ops {int /*<<< orphan*/  rx_filters; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  ptp_clock; TYPE_1__* info; } ;
struct ethtool_ts_info {int so_timestamping; int tx_types; int /*<<< orphan*/  rx_filters; int /*<<< orphan*/  phc_index; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_4__ {struct mv88e6xxx_ptp_ops* ptp_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  ptp_support; TYPE_2__* ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int HWTSTAMP_TX_OFF ; 
 int HWTSTAMP_TX_ON ; 
 int SOF_TIMESTAMPING_RAW_HARDWARE ; 
 int SOF_TIMESTAMPING_RX_HARDWARE ; 
 int SOF_TIMESTAMPING_TX_HARDWARE ; 
 int /*<<< orphan*/  ptp_clock_index (int /*<<< orphan*/ ) ; 

int mv88e6xxx_get_ts_info(struct dsa_switch *ds, int port,
			  struct ethtool_ts_info *info)
{
	const struct mv88e6xxx_ptp_ops *ptp_ops;
	struct mv88e6xxx_chip *chip;

	chip = ds->priv;
	ptp_ops = chip->info->ops->ptp_ops;

	if (!chip->info->ptp_support)
		return -EOPNOTSUPP;

	info->so_timestamping =
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;
	info->phc_index = ptp_clock_index(chip->ptp_clock);
	info->tx_types =
		(1 << HWTSTAMP_TX_OFF) |
		(1 << HWTSTAMP_TX_ON);
	info->rx_filters = ptp_ops->rx_filters;

	return 0;
}