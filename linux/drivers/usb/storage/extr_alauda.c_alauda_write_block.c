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
typedef  int /*<<< orphan*/  u16 ;
struct us_data {int /*<<< orphan*/  send_bulk_pipe; scalar_t__ extra; } ;
struct alauda_info {int /*<<< orphan*/  wr_ep; } ;
struct TYPE_2__ {int pagesize; int blocksize; } ;

/* Variables and functions */
 int ALAUDA_BULK_CMD ; 
 int ALAUDA_BULK_WRITE_BLOCK ; 
 TYPE_1__ MEDIA_INFO (struct us_data*) ; 
 int MEDIA_PORT (struct us_data*) ; 
 int PBA_HI (int /*<<< orphan*/ ) ; 
 int PBA_LO (int /*<<< orphan*/ ) ; 
 int PBA_ZONE (int /*<<< orphan*/ ) ; 
 int USB_STOR_XFER_GOOD ; 
 int alauda_check_status2 (struct us_data*) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alauda_write_block(struct us_data *us, u16 pba, unsigned char *data)
{
	int rc;
	struct alauda_info *info = (struct alauda_info *) us->extra;
	unsigned char command[] = {
		ALAUDA_BULK_CMD, ALAUDA_BULK_WRITE_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba), 32, 0, MEDIA_PORT(us)
	};

	usb_stor_dbg(us, "pba %d\n", pba);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	rc = usb_stor_bulk_transfer_buf(us, info->wr_ep, data,
		(MEDIA_INFO(us).pagesize + 64) * MEDIA_INFO(us).blocksize,
		NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	return alauda_check_status2(us);
}