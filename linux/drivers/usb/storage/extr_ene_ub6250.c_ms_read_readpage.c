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
typedef  int u32 ;
struct us_data {scalar_t__ extra; scalar_t__ iobuf; } ;
struct ms_lib_type_extdat {int intr; int status0; int status1; int ovrflg; int mngflg; int /*<<< orphan*/  logadr; scalar_t__ reserved; } ;
struct ene_ub6250_info {int* bbuf; } ;
struct bulk_cb_wrap {int DataTransferLength; int* CDB; void* Flags; void* Signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDIR_READ ; 
 int /*<<< orphan*/  MS_RW_PATTERN ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_BULK_CB_SIGN ; 
 void* US_BULK_FLAG_IN ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ene_load_bincode (struct us_data*,int /*<<< orphan*/ ) ; 
 int ene_send_scsi_cmd (struct us_data*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bulk_cb_wrap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memstick_logaddr (int,int) ; 

__attribute__((used)) static int ms_read_readpage(struct us_data *us, u32 PhyBlockAddr,
		u8 PageNum, u32 *PageBuf, struct ms_lib_type_extdat *ExtraDat)
{
	struct bulk_cb_wrap *bcb = (struct bulk_cb_wrap *) us->iobuf;
	struct ene_ub6250_info *info = (struct ene_ub6250_info *) us->extra;
	u8 *bbuf = info->bbuf;
	int result;
	u32 bn = PhyBlockAddr * 0x20 + PageNum;

	result = ene_load_bincode(us, MS_RW_PATTERN);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	/* Read Page Data */
	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x200;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;

	bcb->CDB[1]     = 0x02; /* in init.c ENE_MSInit() is 0x01 */

	bcb->CDB[5]     = (unsigned char)(bn);
	bcb->CDB[4]     = (unsigned char)(bn>>8);
	bcb->CDB[3]     = (unsigned char)(bn>>16);
	bcb->CDB[2]     = (unsigned char)(bn>>24);

	result = ene_send_scsi_cmd(us, FDIR_READ, PageBuf, 0);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;


	/* Read Extra Data */
	memset(bcb, 0, sizeof(struct bulk_cb_wrap));
	bcb->Signature = cpu_to_le32(US_BULK_CB_SIGN);
	bcb->DataTransferLength = 0x4;
	bcb->Flags      = US_BULK_FLAG_IN;
	bcb->CDB[0]     = 0xF1;
	bcb->CDB[1]     = 0x03;

	bcb->CDB[5]     = (unsigned char)(PageNum);
	bcb->CDB[4]     = (unsigned char)(PhyBlockAddr);
	bcb->CDB[3]     = (unsigned char)(PhyBlockAddr>>8);
	bcb->CDB[2]     = (unsigned char)(PhyBlockAddr>>16);
	bcb->CDB[6]     = 0x01;

	result = ene_send_scsi_cmd(us, FDIR_READ, bbuf, 0);
	if (result != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	ExtraDat->reserved = 0;
	ExtraDat->intr     = 0x80;  /* Not yet,fireware support */
	ExtraDat->status0  = 0x10;  /* Not yet,fireware support */

	ExtraDat->status1  = 0x00;  /* Not yet,fireware support */
	ExtraDat->ovrflg   = bbuf[0];
	ExtraDat->mngflg   = bbuf[1];
	ExtraDat->logadr   = memstick_logaddr(bbuf[2], bbuf[3]);

	return USB_STOR_TRANSPORT_GOOD;
}