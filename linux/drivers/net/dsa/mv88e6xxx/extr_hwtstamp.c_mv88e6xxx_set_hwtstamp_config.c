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
struct mv88e6xxx_ptp_ops {int rx_filters; int /*<<< orphan*/  (* global_disable ) (struct mv88e6xxx_chip*) ;int /*<<< orphan*/  (* port_disable ) (struct mv88e6xxx_chip*,int) ;int /*<<< orphan*/  (* port_enable ) (struct mv88e6xxx_chip*,int) ;int /*<<< orphan*/  (* global_enable ) (struct mv88e6xxx_chip*) ;} ;
struct mv88e6xxx_port_hwtstamp {int /*<<< orphan*/  state; } ;
struct mv88e6xxx_chip {int enable_count; int /*<<< orphan*/  dev; struct mv88e6xxx_port_hwtstamp* port_hwtstamp; TYPE_2__* info; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {struct mv88e6xxx_ptp_ops* ptp_ops; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 140 
#define  HWTSTAMP_FILTER_NONE 139 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 136 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 135 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 133 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 132 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 131 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 130 
#define  HWTSTAMP_TX_OFF 129 
#define  HWTSTAMP_TX_ON 128 
 int /*<<< orphan*/  MV88E6XXX_HWTSTAMP_ENABLED ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  stub2 (struct mv88e6xxx_chip*,int) ; 
 int /*<<< orphan*/  stub3 (struct mv88e6xxx_chip*,int) ; 
 int /*<<< orphan*/  stub4 (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static int mv88e6xxx_set_hwtstamp_config(struct mv88e6xxx_chip *chip, int port,
					 struct hwtstamp_config *config)
{
	const struct mv88e6xxx_ptp_ops *ptp_ops = chip->info->ops->ptp_ops;
	struct mv88e6xxx_port_hwtstamp *ps = &chip->port_hwtstamp[port];
	bool tstamp_enable = false;

	/* Prevent the TX/RX paths from trying to interact with the
	 * timestamp hardware while we reconfigure it.
	 */
	clear_bit_unlock(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state);

	/* reserved for future extensions */
	if (config->flags)
		return -EINVAL;

	switch (config->tx_type) {
	case HWTSTAMP_TX_OFF:
		tstamp_enable = false;
		break;
	case HWTSTAMP_TX_ON:
		tstamp_enable = true;
		break;
	default:
		return -ERANGE;
	}

	/* The switch supports timestamping both L2 and L4; one cannot be
	 * disabled independently of the other.
	 */

	if (!(BIT(config->rx_filter) & ptp_ops->rx_filters)) {
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		dev_dbg(chip->dev, "Unsupported rx_filter %d\n",
			config->rx_filter);
		return -ERANGE;
	}

	switch (config->rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		tstamp_enable = false;
		break;
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		break;
	case HWTSTAMP_FILTER_ALL:
	default:
		config->rx_filter = HWTSTAMP_FILTER_NONE;
		return -ERANGE;
	}

	mv88e6xxx_reg_lock(chip);
	if (tstamp_enable) {
		chip->enable_count += 1;
		if (chip->enable_count == 1 && ptp_ops->global_enable)
			ptp_ops->global_enable(chip);
		if (ptp_ops->port_enable)
			ptp_ops->port_enable(chip, port);
	} else {
		if (ptp_ops->port_disable)
			ptp_ops->port_disable(chip, port);
		chip->enable_count -= 1;
		if (chip->enable_count == 0 && ptp_ops->global_disable)
			ptp_ops->global_disable(chip);
	}
	mv88e6xxx_reg_unlock(chip);

	/* Once hardware has been configured, enable timestamp checks
	 * in the RX/TX paths.
	 */
	if (tstamp_enable)
		set_bit(MV88E6XXX_HWTSTAMP_ENABLED, &ps->state);

	return 0;
}