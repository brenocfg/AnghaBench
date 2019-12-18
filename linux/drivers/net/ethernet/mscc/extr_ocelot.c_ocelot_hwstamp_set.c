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
struct ocelot_port {int /*<<< orphan*/  ptp_cmd; struct ocelot* ocelot; } ;
struct ocelot {int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  hwtstamp_config; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct hwtstamp_config {int tx_type; int rx_filter; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  cfg ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ERANGE ; 
#define  HWTSTAMP_FILTER_ALL 146 
#define  HWTSTAMP_FILTER_NONE 145 
#define  HWTSTAMP_FILTER_NTP_ALL 144 
#define  HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ 143 
#define  HWTSTAMP_FILTER_PTP_V1_L4_EVENT 142 
#define  HWTSTAMP_FILTER_PTP_V1_L4_SYNC 141 
#define  HWTSTAMP_FILTER_PTP_V2_DELAY_REQ 140 
#define  HWTSTAMP_FILTER_PTP_V2_EVENT 139 
#define  HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ 138 
#define  HWTSTAMP_FILTER_PTP_V2_L2_EVENT 137 
#define  HWTSTAMP_FILTER_PTP_V2_L2_SYNC 136 
#define  HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ 135 
#define  HWTSTAMP_FILTER_PTP_V2_L4_EVENT 134 
#define  HWTSTAMP_FILTER_PTP_V2_L4_SYNC 133 
#define  HWTSTAMP_FILTER_PTP_V2_SYNC 132 
#define  HWTSTAMP_FILTER_SOME 131 
#define  HWTSTAMP_TX_OFF 130 
#define  HWTSTAMP_TX_ON 129 
#define  HWTSTAMP_TX_ONESTEP_SYNC 128 
 int /*<<< orphan*/  IFH_REW_OP_ORIGIN_PTP ; 
 int /*<<< orphan*/  IFH_REW_OP_TWO_STEP_PTP ; 
 scalar_t__ copy_from_user (struct hwtstamp_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct hwtstamp_config*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocelot_hwstamp_set(struct ocelot_port *port, struct ifreq *ifr)
{
	struct ocelot *ocelot = port->ocelot;
	struct hwtstamp_config cfg;

	if (copy_from_user(&cfg, ifr->ifr_data, sizeof(cfg)))
		return -EFAULT;

	/* reserved for future extensions */
	if (cfg.flags)
		return -EINVAL;

	/* Tx type sanity check */
	switch (cfg.tx_type) {
	case HWTSTAMP_TX_ON:
		port->ptp_cmd = IFH_REW_OP_TWO_STEP_PTP;
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		/* IFH_REW_OP_ONE_STEP_PTP updates the correctional field, we
		 * need to update the origin time.
		 */
		port->ptp_cmd = IFH_REW_OP_ORIGIN_PTP;
		break;
	case HWTSTAMP_TX_OFF:
		port->ptp_cmd = 0;
		break;
	default:
		return -ERANGE;
	}

	mutex_lock(&ocelot->ptp_lock);

	switch (cfg.rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		break;
	case HWTSTAMP_FILTER_ALL:
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_NTP_ALL:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		cfg.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		break;
	default:
		mutex_unlock(&ocelot->ptp_lock);
		return -ERANGE;
	}

	/* Commit back the result & save it */
	memcpy(&ocelot->hwtstamp_config, &cfg, sizeof(cfg));
	mutex_unlock(&ocelot->ptp_lock);

	return copy_to_user(ifr->ifr_data, &cfg, sizeof(cfg)) ? -EFAULT : 0;
}