#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int antennaGain; } ;
struct TYPE_9__ {int antennaGain; } ;
struct TYPE_8__ {int ant_div_control; } ;
struct TYPE_7__ {int opFlags; } ;
struct ar9300_base_eep_hdr {int deviceCap; int rfSilent; int txrxMask; int featureEnable; int miscConfiguration; TYPE_2__ opCapFlags; int /*<<< orphan*/ * regDmn; } ;
struct ar9300_eeprom {TYPE_5__ modalHeader2G; TYPE_4__ modalHeader5G; TYPE_3__ base_ext1; int /*<<< orphan*/  macAddr; struct ar9300_base_eep_hdr baseEepHeader; } ;
struct TYPE_6__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
typedef  enum eeprom_param { ____Placeholder_eeprom_param } eeprom_param ;

/* Variables and functions */
 int AR9300_EEP_ANTDIV_CONTROL_DEFAULT_VALUE ; 
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 int BIT (int) ; 
#define  EEP_ANTENNA_GAIN_2G 141 
#define  EEP_ANTENNA_GAIN_5G 140 
#define  EEP_ANT_DIV_CTL1 139 
#define  EEP_CHAIN_MASK_REDUCE 138 
#define  EEP_MAC_LSW 137 
#define  EEP_MAC_MID 136 
#define  EEP_MAC_MSW 135 
#define  EEP_OP_CAP 134 
#define  EEP_OP_MODE 133 
#define  EEP_PAPRD 132 
#define  EEP_REG_0 131 
#define  EEP_RF_SILENT 130 
#define  EEP_RX_MASK 129 
#define  EEP_TX_MASK 128 
 int get_unaligned_be16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ath9k_hw_ar9300_get_eeprom(struct ath_hw *ah,
				      enum eeprom_param param)
{
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	struct ar9300_base_eep_hdr *pBase = &eep->baseEepHeader;

	switch (param) {
	case EEP_MAC_LSW:
		return get_unaligned_be16(eep->macAddr);
	case EEP_MAC_MID:
		return get_unaligned_be16(eep->macAddr + 2);
	case EEP_MAC_MSW:
		return get_unaligned_be16(eep->macAddr + 4);
	case EEP_REG_0:
		return le16_to_cpu(pBase->regDmn[0]);
	case EEP_OP_CAP:
		return pBase->deviceCap;
	case EEP_OP_MODE:
		return pBase->opCapFlags.opFlags;
	case EEP_RF_SILENT:
		return pBase->rfSilent;
	case EEP_TX_MASK:
		return (pBase->txrxMask >> 4) & 0xf;
	case EEP_RX_MASK:
		return pBase->txrxMask & 0xf;
	case EEP_PAPRD:
		return !!(pBase->featureEnable & BIT(5));
	case EEP_CHAIN_MASK_REDUCE:
		return (pBase->miscConfiguration >> 0x3) & 0x1;
	case EEP_ANT_DIV_CTL1:
		if (AR_SREV_9565(ah))
			return AR9300_EEP_ANTDIV_CONTROL_DEFAULT_VALUE;
		else
			return eep->base_ext1.ant_div_control;
	case EEP_ANTENNA_GAIN_5G:
		return eep->modalHeader5G.antennaGain;
	case EEP_ANTENNA_GAIN_2G:
		return eep->modalHeader2G.antennaGain;
	default:
		return 0;
	}
}