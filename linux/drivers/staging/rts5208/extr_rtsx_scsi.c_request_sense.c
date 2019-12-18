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
typedef  int /*<<< orphan*/  u16 ;
struct sense_data_t {int dummy; } ;
struct scsi_cmnd {int dummy; } ;
struct ms_info {scalar_t__ format_status; scalar_t__ progress; scalar_t__ pro_under_formatting; } ;
struct rtsx_chip {struct sense_data_t* sense_buffer; struct ms_info ms_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUR_ERR ; 
 scalar_t__ FORMAT_IN_PROGRESS ; 
 scalar_t__ FORMAT_SUCCESS ; 
 scalar_t__ MS_CARD ; 
 int /*<<< orphan*/  RTSX_STAT_RUN ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_FORMAT_CMD_FAILED ; 
 int /*<<< orphan*/  SENSE_TYPE_NO_SENSE ; 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_GOOD ; 
 scalar_t__ get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_set_stat (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_stor_set_xfer_buf (unsigned char*,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_data (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (unsigned char*) ; 
 unsigned char* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_sense(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	struct sense_data_t *sense;
	unsigned int lun = SCSI_LUN(srb);
	struct ms_info *ms_card = &chip->ms_card;
	unsigned char *tmp, *buf;

	sense = &chip->sense_buffer[lun];

	if ((get_lun_card(chip, lun) == MS_CARD) &&
	    ms_card->pro_under_formatting) {
		if (ms_card->format_status == FORMAT_SUCCESS) {
			set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
			ms_card->pro_under_formatting = 0;
			ms_card->progress = 0;
		} else if (ms_card->format_status == FORMAT_IN_PROGRESS) {
			/* Logical Unit Not Ready Format in Progress */
			set_sense_data(chip, lun, CUR_ERR, 0x02, 0, 0x04, 0x04,
				       0, (u16)(ms_card->progress));
		} else {
			/* Format Command Failed */
			set_sense_type(chip, lun, SENSE_TYPE_FORMAT_CMD_FAILED);
			ms_card->pro_under_formatting = 0;
			ms_card->progress = 0;
		}

		rtsx_set_stat(chip, RTSX_STAT_RUN);
	}

	buf = vmalloc(scsi_bufflen(srb));
	if (!buf)
		return TRANSPORT_ERROR;

	tmp = (unsigned char *)sense;
	memcpy(buf, tmp, scsi_bufflen(srb));

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	vfree(buf);

	scsi_set_resid(srb, 0);
	/* Reset Sense Data */
	set_sense_type(chip, lun, SENSE_TYPE_NO_SENSE);
	return TRANSPORT_GOOD;
}