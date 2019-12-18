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
typedef  int u32 ;
struct scsi_cmnd {int dummy; } ;
struct rtsx_chip {int /*<<< orphan*/  lun_mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHK_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_CHANGE ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int TRANSPORT_ERROR ; 
 int TRANSPORT_FAILED ; 
 int TRANSPORT_GOOD ; 
 int /*<<< orphan*/  check_card_ready (struct rtsx_chip*,unsigned int) ; 
 int get_card_size (struct rtsx_chip*,unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_stor_set_xfer_buf (unsigned char*,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_capacity(struct scsi_cmnd *srb, struct rtsx_chip *chip)
{
	unsigned char *buf;
	unsigned int lun = SCSI_LUN(srb);
	u32 card_size;

	if (!check_card_ready(chip, lun)) {
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
		return TRANSPORT_FAILED;
	}

	if (!(CHK_BIT(chip->lun_mc, lun))) {
		SET_BIT(chip->lun_mc, lun);
		set_sense_type(chip, lun, SENSE_TYPE_MEDIA_CHANGE);
		return TRANSPORT_FAILED;
	}

	buf = kmalloc(8, GFP_KERNEL);
	if (!buf)
		return TRANSPORT_ERROR;

	card_size = get_card_size(chip, lun);
	buf[0] = (unsigned char)((card_size - 1) >> 24);
	buf[1] = (unsigned char)((card_size - 1) >> 16);
	buf[2] = (unsigned char)((card_size - 1) >> 8);
	buf[3] = (unsigned char)(card_size - 1);

	buf[4] = 0x00;
	buf[5] = 0x00;
	buf[6] = 0x02;
	buf[7] = 0x00;

	rtsx_stor_set_xfer_buf(buf, scsi_bufflen(srb), srb);
	kfree(buf);

	scsi_set_resid(srb, 0);

	return TRANSPORT_GOOD;
}