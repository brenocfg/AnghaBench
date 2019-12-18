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
struct scsi_cmnd {int dummy; } ;
struct rtsx_chip {int* lun2card; scalar_t__ mspro_formatter_enable; } ;

/* Variables and functions */
 scalar_t__ CHECK_LUN_MODE (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int CMD_QUE ; 
 int DRCT_ACCESS_DEV ; 
 int LINKED ; 
 int MS_CARD ; 
 int QULIFIRE ; 
 int REL_ADR ; 
 int RMB_DISC ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int SD_CARD ; 
 int /*<<< orphan*/  SD_MS_1LUN ; 
 int /*<<< orphan*/  SD_MS_2LUN ; 
 int SFT_RE ; 
 int SYNC ; 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_GOOD ; 
 int WBUS_16 ; 
 int WBUS_32 ; 
 unsigned char* formatter_inquiry_str ; 
 int get_lun_card (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned char) ; 
 int /*<<< orphan*/  rtsx_stor_set_xfer_buf (unsigned char*,int,struct scsi_cmnd*) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (unsigned char*,char*,unsigned char) ; 
 int /*<<< orphan*/  vfree (unsigned char*) ; 
 unsigned char* vmalloc (int) ; 

__attribute__((used)) static int inquiry(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned int lun = SCSI_LUN(srb);
	char *inquiry_default = (char *)"Generic-xD/SD/M.S.      1.00 ";
	char *inquiry_sdms =    (char *)"Generic-SD/MemoryStick  1.00 ";
	char *inquiry_sd =      (char *)"Generic-SD/MMC          1.00 ";
	char *inquiry_ms =      (char *)"Generic-MemoryStick     1.00 ";
	char *inquiry_string;
	unsigned char sendbytes;
	unsigned char *buf;
	u8 card = get_lun_card(chip, lun);
	bool pro_formatter_flag = false;
	unsigned char inquiry_buf[] = {
		QULIFIRE | DRCT_ACCESS_DEV,
		RMB_DISC | 0x0D,
		0x00,
		0x01,
		0x1f,
		0x02,
		0,
		REL_ADR | WBUS_32 | WBUS_16 | SYNC | LINKED | CMD_QUE | SFT_RE,
	};

	if (CHECK_LUN_MODE(chip, SD_MS_2LUN)) {
		if (chip->lun2card[lun] == SD_CARD)
			inquiry_string = inquiry_sd;
		else
			inquiry_string = inquiry_ms;

	} else if (CHECK_LUN_MODE(chip, SD_MS_1LUN)) {
		inquiry_string = inquiry_sdms;
	} else {
		inquiry_string = inquiry_default;
	}

	buf = vmalloc(scsi_bufflen(srb));
	if (!buf)
		return TRANSPORT_ERROR;

#ifdef SUPPORT_MAGIC_GATE
	if ((chip->mspro_formatter_enable) &&
	    (chip->lun2card[lun] & MS_CARD))
#else
	if (chip->mspro_formatter_enable)
#endif
		if (!card || (card == MS_CARD))
			pro_formatter_flag = true;

	if (pro_formatter_flag) {
		if (scsi_bufflen(srb) < 56)
			sendbytes = (unsigned char)(scsi_bufflen(srb));
		else
			sendbytes = 56;

	} else {
		if (scsi_bufflen(srb) < 36)
			sendbytes = (unsigned char)(scsi_bufflen(srb));
		else
			sendbytes = 36;
	}

	if (sendbytes > 8) {
		memcpy(buf, inquiry_buf, 8);
		strncpy(buf + 8, inquiry_string, sendbytes - 8);
		if (pro_formatter_flag) {
			/* Additional Length */
			buf[4] = 0x33;
		}
	} else {
		memcpy(buf, inquiry_buf, sendbytes);
	}

	if (pro_formatter_flag) {
		if (sendbytes > 36)
			memcpy(buf + 36, formatter_inquiry_str, sendbytes - 36);
	}

	scsi_set_resid(srb, 0);

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	vfree(buf);

	return TRANSPORT_GOOD;
}