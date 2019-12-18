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
struct rtsx_chip {int dummy; } ;

/* Variables and functions */
 int ASCQ_INVLD_CDB ; 
 int ASC_INVLD_CDB ; 
 int /*<<< orphan*/  CDB_ILLEGAL ; 
 int /*<<< orphan*/  CUR_ERR ; 
 int ILGAL_REQ ; 
#define  SENSE_TYPE_FORMAT_CMD_FAILED 143 
#define  SENSE_TYPE_FORMAT_IN_PROGRESS 142 
#define  SENSE_TYPE_MEDIA_CHANGE 141 
#define  SENSE_TYPE_MEDIA_INVALID_CMD_FIELD 140 
#define  SENSE_TYPE_MEDIA_LBA_OVER_RANGE 139 
#define  SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT 138 
#define  SENSE_TYPE_MEDIA_NOT_PRESENT 137 
#define  SENSE_TYPE_MEDIA_READ_FORBIDDEN 136 
#define  SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR 135 
#define  SENSE_TYPE_MEDIA_WRITE_ERR 134 
#define  SENSE_TYPE_MEDIA_WRITE_PROTECT 133 
#define  SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM 132 
#define  SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN 131 
#define  SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB 130 
#define  SENSE_TYPE_MG_WRITE_ERR 129 
#define  SENSE_TYPE_NO_SENSE 128 
 int /*<<< orphan*/  set_sense_data (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 

void set_sense_type(struct rtsx_chip *chip, unsigned int lun, int sense_type)
{
	switch (sense_type) {
	case SENSE_TYPE_MEDIA_CHANGE:
		set_sense_data(chip, lun, CUR_ERR, 0x06, 0, 0x28, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_NOT_PRESENT:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x3A, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_LBA_OVER_RANGE:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x21, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_LUN_NOT_SUPPORT:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x25, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_WRITE_PROTECT:
		set_sense_data(chip, lun, CUR_ERR, 0x07, 0, 0x27, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x11, 0, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_WRITE_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x02, 0, 0);
		break;

	case SENSE_TYPE_MEDIA_INVALID_CMD_FIELD:
		set_sense_data(chip, lun, CUR_ERR, ILGAL_REQ, 0,
			       ASC_INVLD_CDB, ASCQ_INVLD_CDB, CDB_ILLEGAL, 1);
		break;

	case SENSE_TYPE_FORMAT_IN_PROGRESS:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04, 0, 0);
		break;

	case SENSE_TYPE_FORMAT_CMD_FAILED:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x31, 0x01, 0, 0);
		break;

#ifdef SUPPORT_MAGIC_GATE
	case SENSE_TYPE_MG_KEY_FAIL_NOT_ESTAB:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x02, 0, 0);
		break;

	case SENSE_TYPE_MG_KEY_FAIL_NOT_AUTHEN:
		set_sense_data(chip, lun, CUR_ERR, 0x05, 0, 0x6F, 0x00, 0, 0);
		break;

	case SENSE_TYPE_MG_INCOMPATIBLE_MEDIUM:
		set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x30, 0x00, 0, 0);
		break;

	case SENSE_TYPE_MG_WRITE_ERR:
		set_sense_data(chip, lun, CUR_ERR, 0x03, 0, 0x0C, 0x00, 0, 0);
		break;
#endif

#ifdef SUPPORT_SD_LOCK
	case SENSE_TYPE_MEDIA_READ_FORBIDDEN:
		set_sense_data(chip, lun, CUR_ERR, 0x07, 0, 0x11, 0x13, 0, 0);
		break;
#endif

	case SENSE_TYPE_NO_SENSE:
	default:
		set_sense_data(chip, lun, CUR_ERR, 0, 0, 0, 0, 0, 0);
		break;
	}
}