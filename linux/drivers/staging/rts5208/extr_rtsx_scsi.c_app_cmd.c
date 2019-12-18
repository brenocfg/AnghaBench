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
struct scsi_cmnd {int* cmnd; } ;
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
#define  DMA_READ 147 
#define  DMA_WRITE 146 
#define  ERASE_EEPROM2 145 
#define  GET_DEV_STATUS 144 
#define  GET_VAR 143 
#define  PP_READ10 142 
#define  PP_WRITE10 141 
#define  READ_CFG 140 
#define  READ_EEPROM2 139 
#define  READ_EFUSE 138 
#define  READ_HOST_REG 137 
#define  READ_PHY 136 
 int /*<<< orphan*/  SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD ; 
#define  SET_CHIP_MODE 135 
#define  SET_VAR 134 
#define  SUIT_CMD 133 
 int TRANSPORT_FAILED ; 
#define  WRITE_CFG 132 
#define  WRITE_EEPROM2 131 
#define  WRITE_EFUSE 130 
#define  WRITE_HOST_REG 129 
#define  WRITE_PHY 128 
 int dma_access_ring_buffer (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int erase_eeprom2 (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int get_dev_status (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int get_variable (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_cfg_byte (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_eeprom2 (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_efuse (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_host_reg (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_phy_register (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int read_write (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int set_chip_mode (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_variable (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int suit_cmd (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_cfg_byte (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_eeprom2 (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_efuse (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_host_reg (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int write_phy_register (struct scsi_cmnd*,struct rtsx_chip*) ; 

__attribute__((used)) static int app_cmd(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	int result;

	switch (srb->cmnd[2]) {
	case PP_READ10:
	case PP_WRITE10:
		result = read_write(srb, chip);
		break;

	case READ_HOST_REG:
		result = read_host_reg(srb, chip);
		break;

	case WRITE_HOST_REG:
		result = write_host_reg(srb, chip);
		break;

	case GET_VAR:
		result = get_variable(srb, chip);
		break;

	case SET_VAR:
		result = set_variable(srb, chip);
		break;

	case DMA_READ:
	case DMA_WRITE:
		result = dma_access_ring_buffer(srb, chip);
		break;

	case READ_PHY:
		result = read_phy_register(srb, chip);
		break;

	case WRITE_PHY:
		result = write_phy_register(srb, chip);
		break;

	case ERASE_EEPROM2:
		result = erase_eeprom2(srb, chip);
		break;

	case READ_EEPROM2:
		result = read_eeprom2(srb, chip);
		break;

	case WRITE_EEPROM2:
		result = write_eeprom2(srb, chip);
		break;

	case READ_EFUSE:
		result = read_efuse(srb, chip);
		break;

	case WRITE_EFUSE:
		result = write_efuse(srb, chip);
		break;

	case READ_CFG:
		result = read_cfg_byte(srb, chip);
		break;

	case WRITE_CFG:
		result = write_cfg_byte(srb, chip);
		break;

	case SET_CHIP_MODE:
		result = set_chip_mode(srb, chip);
		break;

	case SUIT_CMD:
		result = suit_cmd(srb, chip);
		break;

	case GET_DEV_STATUS:
		result = get_dev_status(srb, chip);
		break;

	default:
		set_sense_type(chip, SCSI_LUN(srb),
			       SENSE_TYPE_MEDIA_INVALID_CMD_FIELD);
		return TRANSPORT_FAILED;
	}

	return result;
}