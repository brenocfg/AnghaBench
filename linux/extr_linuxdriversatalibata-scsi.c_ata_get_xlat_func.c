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
struct ata_device {int flags; } ;
typedef  int /*<<< orphan*/ * ata_xlat_func_t ;

/* Variables and functions */
#define  ATA_12 147 
#define  ATA_16 146 
 int ATA_DFLAG_TRUSTED ; 
#define  MODE_SELECT 145 
#define  MODE_SELECT_10 144 
#define  READ_10 143 
#define  READ_16 142 
#define  READ_6 141 
#define  SECURITY_PROTOCOL_IN 140 
#define  SECURITY_PROTOCOL_OUT 139 
#define  START_STOP 138 
#define  SYNCHRONIZE_CACHE 137 
#define  VARIABLE_LENGTH_CMD 136 
#define  VERIFY 135 
#define  VERIFY_16 134 
#define  WRITE_10 133 
#define  WRITE_16 132 
#define  WRITE_6 131 
#define  WRITE_SAME_16 130 
#define  ZBC_IN 129 
#define  ZBC_OUT 128 
 int /*<<< orphan*/ * ata_scsi_flush_xlat ; 
 int /*<<< orphan*/ * ata_scsi_mode_select_xlat ; 
 int /*<<< orphan*/ * ata_scsi_pass_thru ; 
 int /*<<< orphan*/ * ata_scsi_rw_xlat ; 
 int /*<<< orphan*/ * ata_scsi_security_inout_xlat ; 
 int /*<<< orphan*/ * ata_scsi_start_stop_xlat ; 
 int /*<<< orphan*/ * ata_scsi_var_len_cdb_xlat ; 
 int /*<<< orphan*/ * ata_scsi_verify_xlat ; 
 int /*<<< orphan*/ * ata_scsi_write_same_xlat ; 
 int /*<<< orphan*/ * ata_scsi_zbc_in_xlat ; 
 int /*<<< orphan*/ * ata_scsi_zbc_out_xlat ; 
 int /*<<< orphan*/  ata_try_flush_cache (struct ata_device*) ; 

__attribute__((used)) static inline ata_xlat_func_t ata_get_xlat_func(struct ata_device *dev, u8 cmd)
{
	switch (cmd) {
	case READ_6:
	case READ_10:
	case READ_16:

	case WRITE_6:
	case WRITE_10:
	case WRITE_16:
		return ata_scsi_rw_xlat;

	case WRITE_SAME_16:
		return ata_scsi_write_same_xlat;

	case SYNCHRONIZE_CACHE:
		if (ata_try_flush_cache(dev))
			return ata_scsi_flush_xlat;
		break;

	case VERIFY:
	case VERIFY_16:
		return ata_scsi_verify_xlat;

	case ATA_12:
	case ATA_16:
		return ata_scsi_pass_thru;

	case VARIABLE_LENGTH_CMD:
		return ata_scsi_var_len_cdb_xlat;

	case MODE_SELECT:
	case MODE_SELECT_10:
		return ata_scsi_mode_select_xlat;
		break;

	case ZBC_IN:
		return ata_scsi_zbc_in_xlat;

	case ZBC_OUT:
		return ata_scsi_zbc_out_xlat;

	case SECURITY_PROTOCOL_IN:
	case SECURITY_PROTOCOL_OUT:
		if (!(dev->flags & ATA_DFLAG_TRUSTED))
			break;
		return ata_scsi_security_inout_xlat;

	case START_STOP:
		return ata_scsi_start_stop_xlat;
	}

	return NULL;
}