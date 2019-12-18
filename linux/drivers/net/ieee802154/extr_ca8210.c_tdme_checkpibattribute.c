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
typedef  int u8 ;

/* Variables and functions */
#define  MAC_ASSOCIATED_PAN_COORD 149 
#define  MAC_ASSOCIATION_PERMIT 148 
#define  MAC_AUTO_REQUEST 147 
#define  MAC_AUTO_REQUEST_KEY_ID_MODE 146 
#define  MAC_AUTO_REQUEST_SECURITY_LEVEL 145 
#define  MAC_BATT_LIFE_EXT 144 
#define  MAC_BATT_LIFE_EXT_PERIODS 143 
#define  MAC_BEACON_ORDER 142 
#define  MAC_BEACON_PAYLOAD 141 
#define  MAC_BEACON_PAYLOAD_LENGTH 140 
#define  MAC_GTS_PERMIT 139 
 int MAC_INVALID_PARAMETER ; 
#define  MAC_MAX_BE 138 
#define  MAC_MAX_CSMA_BACKOFFS 137 
#define  MAC_MAX_FRAME_RETRIES 136 
#define  MAC_MIN_BE 135 
#define  MAC_PROMISCUOUS_MODE 134 
#define  MAC_RESPONSE_WAIT_TIME 133 
#define  MAC_RX_ON_WHEN_IDLE 132 
#define  MAC_SECURITY_ENABLED 131 
 int MAC_SUCCESS ; 
#define  MAC_SUPERFRAME_ORDER 130 
 int MAX_BEACON_PAYLOAD_LENGTH ; 
#define  PHY_CCA_MODE 129 
#define  PHY_TRANSMIT_POWER 128 

__attribute__((used)) static u8 tdme_checkpibattribute(
	u8            pib_attribute,
	u8            pib_attribute_length,
	const void   *pib_attribute_value
)
{
	u8 status = MAC_SUCCESS;
	u8 value;

	value  = *((u8 *)pib_attribute_value);

	switch (pib_attribute) {
	/* PHY */
	case PHY_TRANSMIT_POWER:
		if (value > 0x3F)
			status = MAC_INVALID_PARAMETER;
		break;
	case PHY_CCA_MODE:
		if (value > 0x03)
			status = MAC_INVALID_PARAMETER;
		break;
	/* MAC */
	case MAC_BATT_LIFE_EXT_PERIODS:
		if (value < 6 || value > 41)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_BEACON_PAYLOAD:
		if (pib_attribute_length > MAX_BEACON_PAYLOAD_LENGTH)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_BEACON_PAYLOAD_LENGTH:
		if (value > MAX_BEACON_PAYLOAD_LENGTH)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_BEACON_ORDER:
		if (value > 15)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_MAX_BE:
		if (value < 3 || value > 8)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_MAX_CSMA_BACKOFFS:
		if (value > 5)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_MAX_FRAME_RETRIES:
		if (value > 7)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_MIN_BE:
		if (value > 8)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_RESPONSE_WAIT_TIME:
		if (value < 2 || value > 64)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_SUPERFRAME_ORDER:
		if (value > 15)
			status = MAC_INVALID_PARAMETER;
		break;
	/* boolean */
	case MAC_ASSOCIATED_PAN_COORD:
	case MAC_ASSOCIATION_PERMIT:
	case MAC_AUTO_REQUEST:
	case MAC_BATT_LIFE_EXT:
	case MAC_GTS_PERMIT:
	case MAC_PROMISCUOUS_MODE:
	case MAC_RX_ON_WHEN_IDLE:
	case MAC_SECURITY_ENABLED:
		if (value > 1)
			status = MAC_INVALID_PARAMETER;
		break;
	/* MAC SEC */
	case MAC_AUTO_REQUEST_SECURITY_LEVEL:
		if (value > 7)
			status = MAC_INVALID_PARAMETER;
		break;
	case MAC_AUTO_REQUEST_KEY_ID_MODE:
		if (value > 3)
			status = MAC_INVALID_PARAMETER;
		break;
	default:
		break;
	}

	return status;
}