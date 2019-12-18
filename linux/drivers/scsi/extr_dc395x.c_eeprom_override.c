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
typedef  size_t u8 ;
struct NvRamType {size_t scsi_id; size_t channel_cfg; size_t max_tag; TYPE_1__* target; int /*<<< orphan*/  delay_time; } ;
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {size_t cfg0; size_t period; } ;

/* Variables and functions */
 size_t CFG_ADAPTER_ID ; 
 size_t CFG_ADAPTER_MODE ; 
 size_t CFG_DEV_MODE ; 
 size_t CFG_MAX_SPEED ; 
 scalar_t__ CFG_PARAM_UNSET ; 
 size_t CFG_RESET_DELAY ; 
 size_t CFG_TAGS ; 
 size_t DC395x_MAX_SCSI_ID ; 
 TYPE_2__* cfg_data ; 
 int /*<<< orphan*/  delay_to_eeprom_index (scalar_t__) ; 

__attribute__((used)) static void eeprom_override(struct NvRamType *eeprom)
{
	u8 id;

	/* Adapter Settings */
	if (cfg_data[CFG_ADAPTER_ID].value != CFG_PARAM_UNSET)
		eeprom->scsi_id = (u8)cfg_data[CFG_ADAPTER_ID].value;

	if (cfg_data[CFG_ADAPTER_MODE].value != CFG_PARAM_UNSET)
		eeprom->channel_cfg = (u8)cfg_data[CFG_ADAPTER_MODE].value;

	if (cfg_data[CFG_RESET_DELAY].value != CFG_PARAM_UNSET)
		eeprom->delay_time = delay_to_eeprom_index(
					cfg_data[CFG_RESET_DELAY].value);

	if (cfg_data[CFG_TAGS].value != CFG_PARAM_UNSET)
		eeprom->max_tag = (u8)cfg_data[CFG_TAGS].value;

	/* Device Settings */
	for (id = 0; id < DC395x_MAX_SCSI_ID; id++) {
		if (cfg_data[CFG_DEV_MODE].value != CFG_PARAM_UNSET)
			eeprom->target[id].cfg0 =
				(u8)cfg_data[CFG_DEV_MODE].value;

		if (cfg_data[CFG_MAX_SPEED].value != CFG_PARAM_UNSET)
			eeprom->target[id].period =
				(u8)cfg_data[CFG_MAX_SPEED].value;

	}
}