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
struct us_data {scalar_t__ extra; } ;
struct sense_data {int ErrorCode; int AdditionalSenseLength; scalar_t__ AdditionalSenseCodeQualifier; scalar_t__ AdditionalSenseCode; void* Flags; } ;
struct scsi_cmnd {int /*<<< orphan*/ * sense_buffer; } ;
struct isd200_info {unsigned char* ATARegs; } ;

/* Variables and functions */
 unsigned char ATA_ERROR_MEDIA_CHANGE ; 
 unsigned char ATA_MCR ; 
 size_t ATA_REG_ERROR_OFFSET ; 
 unsigned char ATA_TRK0NF ; 
 unsigned char ATA_UNC ; 
 void* DATA_PROTECT ; 
 void* NOT_READY ; 
 int SENSE_ERRCODE_VALID ; 
 void* UNIT_ATTENTION ; 

__attribute__((used)) static void isd200_build_sense(struct us_data *us, struct scsi_cmnd *srb)
{
	struct isd200_info *info = (struct isd200_info *)us->extra;
	struct sense_data *buf = (struct sense_data *) &srb->sense_buffer[0];
	unsigned char error = info->ATARegs[ATA_REG_ERROR_OFFSET];

	if(error & ATA_ERROR_MEDIA_CHANGE) {
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags = UNIT_ATTENTION;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualifier = 0;
	} else if (error & ATA_MCR) {
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  UNIT_ATTENTION;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualifier = 0;
	} else if (error & ATA_TRK0NF) {
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  NOT_READY;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualifier = 0;
	} else if (error & ATA_UNC) {
		buf->ErrorCode = 0x70 | SENSE_ERRCODE_VALID;
		buf->AdditionalSenseLength = 0xb;
		buf->Flags =  DATA_PROTECT;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualifier = 0;
	} else {
		buf->ErrorCode = 0;
		buf->AdditionalSenseLength = 0;
		buf->Flags =  0;
		buf->AdditionalSenseCode = 0;
		buf->AdditionalSenseCodeQualifier = 0;
	}
}