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
struct xgbe_sfp_eeprom {int* base; } ;
struct xgbe_prv_data {struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ sfp_cable; int sfp_cable_len; int sfp_base; int /*<<< orphan*/  sfp_speed; int /*<<< orphan*/  sfp_rx_los; int /*<<< orphan*/  sfp_tx_fault; struct xgbe_sfp_eeprom sfp_eeprom; } ;

/* Variables and functions */
#define  XGBE_SFP_BASE_10000_CR 136 
#define  XGBE_SFP_BASE_10000_ER 135 
#define  XGBE_SFP_BASE_10000_LR 134 
#define  XGBE_SFP_BASE_10000_LRM 133 
#define  XGBE_SFP_BASE_10000_SR 132 
#define  XGBE_SFP_BASE_1000_CX 131 
#define  XGBE_SFP_BASE_1000_LX 130 
#define  XGBE_SFP_BASE_1000_SX 129 
#define  XGBE_SFP_BASE_1000_T 128 
 size_t XGBE_SFP_BASE_10GBE_CC ; 
 int XGBE_SFP_BASE_10GBE_CC_ER ; 
 int XGBE_SFP_BASE_10GBE_CC_LR ; 
 int XGBE_SFP_BASE_10GBE_CC_LRM ; 
 int XGBE_SFP_BASE_10GBE_CC_SR ; 
 size_t XGBE_SFP_BASE_1GBE_CC ; 
 int XGBE_SFP_BASE_1GBE_CC_CX ; 
 int XGBE_SFP_BASE_1GBE_CC_LX ; 
 int XGBE_SFP_BASE_1GBE_CC_SX ; 
 int XGBE_SFP_BASE_1GBE_CC_T ; 
 size_t XGBE_SFP_BASE_CABLE ; 
 int XGBE_SFP_BASE_CABLE_PASSIVE ; 
 size_t XGBE_SFP_BASE_CU_CABLE_LEN ; 
 size_t XGBE_SFP_BASE_EXT_ID ; 
 size_t XGBE_SFP_BASE_ID ; 
 scalar_t__ XGBE_SFP_CABLE_ACTIVE ; 
 scalar_t__ XGBE_SFP_CABLE_PASSIVE ; 
 int XGBE_SFP_EXT_ID_SFP ; 
 int XGBE_SFP_ID_SFP ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_1000 ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_10000 ; 
 int /*<<< orphan*/  XGBE_SFP_SPEED_100_1000 ; 
 int /*<<< orphan*/  xgbe_phy_check_sfp_rx_los (struct xgbe_phy_data*) ; 
 int /*<<< orphan*/  xgbe_phy_check_sfp_tx_fault (struct xgbe_phy_data*) ; 
 scalar_t__ xgbe_phy_sfp_bit_rate (struct xgbe_sfp_eeprom*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_phy_sfp_parse_eeprom(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	struct xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
	u8 *sfp_base;

	sfp_base = sfp_eeprom->base;

	if (sfp_base[XGBE_SFP_BASE_ID] != XGBE_SFP_ID_SFP)
		return;

	if (sfp_base[XGBE_SFP_BASE_EXT_ID] != XGBE_SFP_EXT_ID_SFP)
		return;

	/* Update transceiver signals (eeprom extd/options) */
	phy_data->sfp_tx_fault = xgbe_phy_check_sfp_tx_fault(phy_data);
	phy_data->sfp_rx_los = xgbe_phy_check_sfp_rx_los(phy_data);

	/* Assume ACTIVE cable unless told it is PASSIVE */
	if (sfp_base[XGBE_SFP_BASE_CABLE] & XGBE_SFP_BASE_CABLE_PASSIVE) {
		phy_data->sfp_cable = XGBE_SFP_CABLE_PASSIVE;
		phy_data->sfp_cable_len = sfp_base[XGBE_SFP_BASE_CU_CABLE_LEN];
	} else {
		phy_data->sfp_cable = XGBE_SFP_CABLE_ACTIVE;
	}

	/* Determine the type of SFP */
	if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_SR)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_SR;
	else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LR)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_LR;
	else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_LRM)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_LRM;
	else if (sfp_base[XGBE_SFP_BASE_10GBE_CC] & XGBE_SFP_BASE_10GBE_CC_ER)
		phy_data->sfp_base = XGBE_SFP_BASE_10000_ER;
	else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_SX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_SX;
	else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_LX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_LX;
	else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_CX)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_CX;
	else if (sfp_base[XGBE_SFP_BASE_1GBE_CC] & XGBE_SFP_BASE_1GBE_CC_T)
		phy_data->sfp_base = XGBE_SFP_BASE_1000_T;
	else if ((phy_data->sfp_cable == XGBE_SFP_CABLE_PASSIVE) &&
		 xgbe_phy_sfp_bit_rate(sfp_eeprom, XGBE_SFP_SPEED_10000))
		phy_data->sfp_base = XGBE_SFP_BASE_10000_CR;

	switch (phy_data->sfp_base) {
	case XGBE_SFP_BASE_1000_T:
		phy_data->sfp_speed = XGBE_SFP_SPEED_100_1000;
		break;
	case XGBE_SFP_BASE_1000_SX:
	case XGBE_SFP_BASE_1000_LX:
	case XGBE_SFP_BASE_1000_CX:
		phy_data->sfp_speed = XGBE_SFP_SPEED_1000;
		break;
	case XGBE_SFP_BASE_10000_SR:
	case XGBE_SFP_BASE_10000_LR:
	case XGBE_SFP_BASE_10000_LRM:
	case XGBE_SFP_BASE_10000_ER:
	case XGBE_SFP_BASE_10000_CR:
		phy_data->sfp_speed = XGBE_SFP_SPEED_10000;
		break;
	default:
		break;
	}
}