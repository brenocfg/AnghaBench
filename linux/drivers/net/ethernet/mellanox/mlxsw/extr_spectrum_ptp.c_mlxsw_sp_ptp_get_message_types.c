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
typedef  int u16 ;
struct hwtstamp_config {int rx_filter; int tx_type; } ;
typedef  enum hwtstamp_tx_types { ____Placeholder_hwtstamp_tx_types } hwtstamp_tx_types ;
typedef  enum hwtstamp_rx_filters { ____Placeholder_hwtstamp_rx_filters } hwtstamp_rx_filters ;

/* Variables and functions */
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

__attribute__((used)) static int mlxsw_sp_ptp_get_message_types(const struct hwtstamp_config *config,
					  u16 *p_ing_types, u16 *p_egr_types,
					  enum hwtstamp_rx_filters *p_rx_filter)
{
	enum hwtstamp_rx_filters rx_filter = config->rx_filter;
	enum hwtstamp_tx_types tx_type = config->tx_type;
	u16 ing_types = 0x00;
	u16 egr_types = 0x00;

	switch (tx_type) {
	case HWTSTAMP_TX_OFF:
		egr_types = 0x00;
		break;
	case HWTSTAMP_TX_ON:
		egr_types = 0xff;
		break;
	case HWTSTAMP_TX_ONESTEP_SYNC:
		return -ERANGE;
	}

	switch (rx_filter) {
	case HWTSTAMP_FILTER_NONE:
		ing_types = 0x00;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	case HWTSTAMP_FILTER_PTP_V2_SYNC:
		ing_types = 0x01;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	case HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		ing_types = 0x02;
		break;
	case HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	case HWTSTAMP_FILTER_PTP_V2_EVENT:
		ing_types = 0x0f;
		break;
	case HWTSTAMP_FILTER_ALL:
		ing_types = 0xff;
		break;
	case HWTSTAMP_FILTER_SOME:
	case HWTSTAMP_FILTER_NTP_ALL:
		return -ERANGE;
	}

	*p_ing_types = ing_types;
	*p_egr_types = egr_types;
	*p_rx_filter = rx_filter;
	return 0;
}