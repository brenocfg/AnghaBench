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
struct us_data {int /*<<< orphan*/  recv_bulk_pipe; int /*<<< orphan*/  send_bulk_pipe; } ;
struct TYPE_2__ {int pagesize; } ;

/* Variables and functions */
 unsigned int ALAUDA_BULK_CMD ; 
 unsigned int ALAUDA_BULK_READ_BLOCK ; 
 TYPE_1__ MEDIA_INFO (struct us_data*) ; 
 unsigned int MEDIA_PORT (struct us_data*) ; 
 unsigned int PBA_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBA_LO (int /*<<< orphan*/ ) ; 
 unsigned int PBA_ZONE (int /*<<< orphan*/ ) ; 
 int USB_STOR_XFER_GOOD ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int alauda_read_block_raw(struct us_data *us, u16 pba,
		unsigned int page, unsigned int pages, unsigned char *data)
{
	int rc;
	unsigned char command[] = {
		ALAUDA_BULK_CMD, ALAUDA_BULK_READ_BLOCK, PBA_HI(pba),
		PBA_ZONE(pba), 0, PBA_LO(pba) + page, pages, 0, MEDIA_PORT(us)
	};

	usb_stor_dbg(us, "pba %d page %d count %d\n", pba, page, pages);

	rc = usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, NULL);
	if (rc != USB_STOR_XFER_GOOD)
		return rc;

	return usb_stor_bulk_transfer_buf(us, us->recv_bulk_pipe,
		data, (MEDIA_INFO(us).pagesize + 64) * pages, NULL);
}