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
struct cyapa {scalar_t__ state; scalar_t__ gen; } ;

/* Variables and functions */
 int BL_ERROR_BOOTLOADING ; 
 int BL_ERROR_NO_ERR_IDLE ; 
 int BL_FILE ; 
 int BL_STATUS_BUSY ; 
 int BL_STATUS_CSUM_VALID ; 
 int BL_STATUS_RUNNING ; 
 scalar_t__ CYAPA_GEN3 ; 
 scalar_t__ CYAPA_STATE_BL_ACTIVE ; 
 scalar_t__ CYAPA_STATE_BL_BUSY ; 
 scalar_t__ CYAPA_STATE_BL_IDLE ; 
 scalar_t__ CYAPA_STATE_NO_DEVICE ; 
 scalar_t__ CYAPA_STATE_OP ; 
 int EAGAIN ; 
 scalar_t__ GEN3_FINGER_NUM (int) ; 
 scalar_t__ GEN3_MAX_FINGERS ; 
 int OP_DATA_VALID ; 
 int OP_STATUS_SRC ; 
 size_t REG_BL_ERROR ; 
 size_t REG_BL_FILE ; 
 size_t REG_BL_STATUS ; 
 size_t REG_OP_DATA1 ; 
 size_t REG_OP_STATUS ; 

__attribute__((used)) static int cyapa_gen3_state_parse(struct cyapa *cyapa, u8 *reg_data, int len)
{
	cyapa->state = CYAPA_STATE_NO_DEVICE;

	/* Parse based on Gen3 characteristic registers and bits */
	if (reg_data[REG_BL_FILE] == BL_FILE &&
		reg_data[REG_BL_ERROR] == BL_ERROR_NO_ERR_IDLE &&
		(reg_data[REG_BL_STATUS] ==
			(BL_STATUS_RUNNING | BL_STATUS_CSUM_VALID) ||
			reg_data[REG_BL_STATUS] == BL_STATUS_RUNNING)) {
		/*
		 * Normal state after power on or reset,
		 * REG_BL_STATUS == 0x11, firmware image checksum is valid.
		 * REG_BL_STATUS == 0x10, firmware image checksum is invalid.
		 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BL_IDLE;
	} else if (reg_data[REG_BL_FILE] == BL_FILE &&
		(reg_data[REG_BL_STATUS] & BL_STATUS_RUNNING) ==
			BL_STATUS_RUNNING) {
		cyapa->gen = CYAPA_GEN3;
		if (reg_data[REG_BL_STATUS] & BL_STATUS_BUSY) {
			cyapa->state = CYAPA_STATE_BL_BUSY;
		} else {
			if ((reg_data[REG_BL_ERROR] & BL_ERROR_BOOTLOADING) ==
					BL_ERROR_BOOTLOADING)
				cyapa->state = CYAPA_STATE_BL_ACTIVE;
			else
				cyapa->state = CYAPA_STATE_BL_IDLE;
		}
	} else if ((reg_data[REG_OP_STATUS] & OP_STATUS_SRC) &&
			(reg_data[REG_OP_DATA1] & OP_DATA_VALID)) {
		/*
		 * Normal state when running in operational mode,
		 * may also not in full power state or
		 * busying in command process.
		 */
		if (GEN3_FINGER_NUM(reg_data[REG_OP_DATA1]) <=
				GEN3_MAX_FINGERS) {
			/* Finger number data is valid. */
			cyapa->gen = CYAPA_GEN3;
			cyapa->state = CYAPA_STATE_OP;
		}
	} else if (reg_data[REG_OP_STATUS] == 0x0C &&
			reg_data[REG_OP_DATA1] == 0x08) {
		/* Op state when first two registers overwritten with 0x00 */
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_OP;
	} else if (reg_data[REG_BL_STATUS] &
			(BL_STATUS_RUNNING | BL_STATUS_BUSY)) {
		cyapa->gen = CYAPA_GEN3;
		cyapa->state = CYAPA_STATE_BL_BUSY;
	}

	if (cyapa->gen == CYAPA_GEN3 && (cyapa->state == CYAPA_STATE_OP ||
		cyapa->state == CYAPA_STATE_BL_IDLE ||
		cyapa->state == CYAPA_STATE_BL_ACTIVE ||
		cyapa->state == CYAPA_STATE_BL_BUSY))
		return 0;

	return -EAGAIN;
}