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
struct max77693_muic_info {int* status; int prev_cable_type; int prev_cable_type_gnd; int prev_chg_type; int /*<<< orphan*/  dev; } ;
typedef  enum max77693_muic_cable_group { ____Placeholder_max77693_muic_cable_group } max77693_muic_cable_group ;

/* Variables and functions */
 int EINVAL ; 
#define  MAX77693_CABLE_GROUP_ADC 131 
#define  MAX77693_CABLE_GROUP_ADC_GND 130 
#define  MAX77693_CABLE_GROUP_CHG 129 
#define  MAX77693_CABLE_GROUP_VBVOLT 128 
 int MAX77693_CHARGER_TYPE_NONE ; 
 int MAX77693_MUIC_ADC_OPEN ; 
 int MAX77693_STATUS1_ADC1K_MASK ; 
 int MAX77693_STATUS1_ADC1K_SHIFT ; 
 int MAX77693_STATUS1_ADCLOW_MASK ; 
 int MAX77693_STATUS1_ADCLOW_SHIFT ; 
 int MAX77693_STATUS1_ADC_MASK ; 
 int MAX77693_STATUS1_ADC_SHIFT ; 
 int MAX77693_STATUS2_CHGTYP_MASK ; 
 int MAX77693_STATUS2_CHGTYP_SHIFT ; 
 int MAX77693_STATUS2_VBVOLT_MASK ; 
 int MAX77693_STATUS2_VBVOLT_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int max77693_muic_get_cable_type(struct max77693_muic_info *info,
		enum max77693_muic_cable_group group, bool *attached)
{
	int cable_type = 0;
	int adc;
	int adc1k;
	int adclow;
	int vbvolt;
	int chg_type;

	switch (group) {
	case MAX77693_CABLE_GROUP_ADC:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type) for handling cable when cable is
		 * detached.
		 */
		if (adc == MAX77693_MUIC_ADC_OPEN) {
			*attached = false;

			cable_type = info->prev_cable_type;
			info->prev_cable_type = MAX77693_MUIC_ADC_OPEN;
		} else {
			*attached = true;

			cable_type = info->prev_cable_type = adc;
		}
		break;
	case MAX77693_CABLE_GROUP_ADC_GND:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;

		/*
		 * Check current cable state/cable type and store cable type
		 * (info->prev_cable_type/_gnd) for handling cable when cable
		 * is detached.
		 */
		if (adc == MAX77693_MUIC_ADC_OPEN) {
			*attached = false;

			cable_type = info->prev_cable_type_gnd;
			info->prev_cable_type_gnd = MAX77693_MUIC_ADC_OPEN;
		} else {
			*attached = true;

			adclow = info->status[0] & MAX77693_STATUS1_ADCLOW_MASK;
			adclow >>= MAX77693_STATUS1_ADCLOW_SHIFT;
			adc1k = info->status[0] & MAX77693_STATUS1_ADC1K_MASK;
			adc1k >>= MAX77693_STATUS1_ADC1K_SHIFT;

			vbvolt = info->status[1] & MAX77693_STATUS2_VBVOLT_MASK;
			vbvolt >>= MAX77693_STATUS2_VBVOLT_SHIFT;

			/**
			 * [0x1|VBVolt|ADCLow|ADC1K]
			 * [0x1|     0|     0|    0] USB_HOST
			 * [0x1|     1|     0|    0] USB_HSOT_VB
			 * [0x1|     0|     1|    0] Audio Video cable with load
			 * [0x1|     0|     1|    1] MHL without charging cable
			 * [0x1|     1|     1|    1] MHL with charging cable
			 */
			cable_type = ((0x1 << 8)
					| (vbvolt << 2)
					| (adclow << 1)
					| adc1k);

			info->prev_cable_type = adc;
			info->prev_cable_type_gnd = cable_type;
		}

		break;
	case MAX77693_CABLE_GROUP_CHG:
		/*
		 * Read charger type to check cable type and decide cable state
		 * according to type of charger cable.
		 */
		chg_type = info->status[1] & MAX77693_STATUS2_CHGTYP_MASK;
		chg_type >>= MAX77693_STATUS2_CHGTYP_SHIFT;

		if (chg_type == MAX77693_CHARGER_TYPE_NONE) {
			*attached = false;

			cable_type = info->prev_chg_type;
			info->prev_chg_type = MAX77693_CHARGER_TYPE_NONE;
		} else {
			*attached = true;

			/*
			 * Check current cable state/cable type and store cable
			 * type(info->prev_chg_type) for handling cable when
			 * charger cable is detached.
			 */
			cable_type = info->prev_chg_type = chg_type;
		}

		break;
	case MAX77693_CABLE_GROUP_VBVOLT:
		/*
		 * Read ADC value to check cable type and decide cable state
		 * according to cable type
		 */
		adc = info->status[0] & MAX77693_STATUS1_ADC_MASK;
		adc >>= MAX77693_STATUS1_ADC_SHIFT;
		chg_type = info->status[1] & MAX77693_STATUS2_CHGTYP_MASK;
		chg_type >>= MAX77693_STATUS2_CHGTYP_SHIFT;

		if (adc == MAX77693_MUIC_ADC_OPEN
				&& chg_type == MAX77693_CHARGER_TYPE_NONE)
			*attached = false;
		else
			*attached = true;

		/*
		 * Read vbvolt field, if vbvolt is 1,
		 * this cable is used for charging.
		 */
		vbvolt = info->status[1] & MAX77693_STATUS2_VBVOLT_MASK;
		vbvolt >>= MAX77693_STATUS2_VBVOLT_SHIFT;

		cable_type = vbvolt;
		break;
	default:
		dev_err(info->dev, "Unknown cable group (%d)\n", group);
		cable_type = -EINVAL;
		break;
	}

	return cable_type;
}