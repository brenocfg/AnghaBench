#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct us_data {int /*<<< orphan*/ * srb; TYPE_1__* pusb_dev; scalar_t__ extra; scalar_t__ iobuf; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct ene_ub6250_info {unsigned char BIN_FLAG; } ;
struct bulk_cb_wrap {int Flags; int* CDB; int /*<<< orphan*/  DataTransferLength; int /*<<< orphan*/  Signature; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDIR_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* MSP_RW_FIRMWARE ; 
#define  MSP_RW_PATTERN 133 
 char* MS_INIT_FIRMWARE ; 
#define  MS_INIT_PATTERN 132 
 char* MS_RW_FIRMWARE ; 
#define  MS_RW_PATTERN 131 
 char* SD_INIT1_FIRMWARE ; 
#define  SD_INIT1_PATTERN 130 
 char* SD_INIT2_FIRMWARE ; 
#define  SD_INIT2_PATTERN 129 
 char* SD_RW_FIRMWARE ; 
#define  SD_RW_PATTERN 128 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ene_send_scsi_cmd (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bulk_cb_wrap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_set_resid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int ene_load_bincode(struct us_data *us, unsigned char flag)
{
	int err;
	char *fw_name = NULL;
	unsigned char *buf = NULL;
	const struct firmware *sd_fw = NULL;
	int result = USB_STOR_TRANSPORT_ERROR;
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;

	if (info->BIN_FLAG == flag)
		return USB_STOR_TRANSPORT_GOOD;

	switch (flag) {
	/* For SD */
	case SD_INIT1_PATTERN:
		usb_stor_dbg(us, "SD_INIT1_PATTERN\n");
		fw_name = SD_INIT1_FIRMWARE;
		break;
	case SD_INIT2_PATTERN:
		usb_stor_dbg(us, "SD_INIT2_PATTERN\n");
		fw_name = SD_INIT2_FIRMWARE;
		break;
	case SD_RW_PATTERN:
		usb_stor_dbg(us, "SD_RW_PATTERN\n");
		fw_name = SD_RW_FIRMWARE;
		break;
	/* For MS */
	case MS_INIT_PATTERN:
		usb_stor_dbg(us, "MS_INIT_PATTERN\n");
		fw_name = MS_INIT_FIRMWARE;
		break;
	case MSP_RW_PATTERN:
		usb_stor_dbg(us, "MSP_RW_PATTERN\n");
		fw_name = MSP_RW_FIRMWARE;
		break;
	case MS_RW_PATTERN:
		usb_stor_dbg(us, "MS_RW_PATTERN\n");
		fw_name = MS_RW_FIRMWARE;
		break;
	default:
		usb_stor_dbg(us, "----------- Unknown PATTERN ----------\n");
		goto nofw;
	}

	err = request_firmware(&sd_fw, fw_name, &us->pusb_dev->dev);
	if (err) {
		usb_stor_dbg(us, "load firmware %s failed\n", fw_name);
		goto nofw;
	}
	buf = kmemdup(sd_fw->data, sd_fw->size, GFP_KERNEL);
	if (buf == NULL)
		goto nofw;

	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = sd_fw->size;
	bcb->Flags = 0x00;
	bcb->CDB[0] = 0xEF;

	result = ene_send_scsi_cmd(us, FDIR_WRITE, buf, 0);
	if (us->srb != NULL)
		scsi_set_resid(us->srb, 0);
	info->BIN_FLAG = flag;
	kfree(buf);

nofw:
	release_firmware(sd_fw);
	return result;
}