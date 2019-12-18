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
typedef  int /*<<< orphan*/  timer_page ;
struct us_data {unsigned char* iobuf; scalar_t__ extra; } ;
struct scsi_cmnd {int* cmnd; } ;
struct jumpshot_info {int sense_key; int sense_asc; int sense_ascq; } ;
typedef  int /*<<< orphan*/  rw_err_page ;
typedef  int /*<<< orphan*/  rbac_page ;
typedef  int /*<<< orphan*/  cache_page ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*) ; 
 int /*<<< orphan*/  usb_stor_set_xfer_buf (unsigned char*,unsigned int,struct scsi_cmnd*) ; 

__attribute__((used)) static int jumpshot_handle_mode_sense(struct us_data *us,
				      struct scsi_cmnd * srb, 
				      int sense_6)
{
	static unsigned char rw_err_page[12] = {
		0x1, 0xA, 0x21, 1, 0, 0, 0, 0, 1, 0, 0, 0
	};
	static unsigned char cache_page[12] = {
		0x8, 0xA, 0x1, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};
	static unsigned char rbac_page[12] = {
		0x1B, 0xA, 0, 0x81, 0, 0, 0, 0, 0, 0, 0, 0
	};
	static unsigned char timer_page[8] = {
		0x1C, 0x6, 0, 0, 0, 0
	};
	unsigned char pc, page_code;
	unsigned int i = 0;
	struct jumpshot_info *info = (struct jumpshot_info *) (us->extra);
	unsigned char *ptr = us->iobuf;

	pc = srb->cmnd[2] >> 6;
	page_code = srb->cmnd[2] & 0x3F;

	switch (pc) {
	   case 0x0:
		   usb_stor_dbg(us, "Current values\n");
		   break;
	   case 0x1:
		   usb_stor_dbg(us, "Changeable values\n");
		   break;
	   case 0x2:
		   usb_stor_dbg(us, "Default values\n");
		   break;
	   case 0x3:
		   usb_stor_dbg(us, "Saves values\n");
		   break;
	}

	memset(ptr, 0, 8);
	if (sense_6) {
		ptr[2] = 0x00;		// WP enable: 0x80
		i = 4;
	} else {
		ptr[3] = 0x00;		// WP enable: 0x80
		i = 8;
	}

	switch (page_code) {
	   case 0x0:
		// vendor-specific mode
		info->sense_key = 0x05;
		info->sense_asc = 0x24;
		info->sense_ascq = 0x00;
		return USB_STOR_TRANSPORT_FAILED;

	   case 0x1:
		memcpy(ptr + i, rw_err_page, sizeof(rw_err_page));
		i += sizeof(rw_err_page);
		break;

	   case 0x8:
		memcpy(ptr + i, cache_page, sizeof(cache_page));
		i += sizeof(cache_page);
		break;

	   case 0x1B:
		memcpy(ptr + i, rbac_page, sizeof(rbac_page));
		i += sizeof(rbac_page);
		break;

	   case 0x1C:
		memcpy(ptr + i, timer_page, sizeof(timer_page));
		i += sizeof(timer_page);
		break;

	   case 0x3F:
		memcpy(ptr + i, timer_page, sizeof(timer_page));
		i += sizeof(timer_page);
		memcpy(ptr + i, rbac_page, sizeof(rbac_page));
		i += sizeof(rbac_page);
		memcpy(ptr + i, cache_page, sizeof(cache_page));
		i += sizeof(cache_page);
		memcpy(ptr + i, rw_err_page, sizeof(rw_err_page));
		i += sizeof(rw_err_page);
		break;
	}

	if (sense_6)
		ptr[0] = i - 1;
	else
		((__be16 *) ptr)[0] = cpu_to_be16(i - 2);
	usb_stor_set_xfer_buf(ptr, i, srb);

	return USB_STOR_TRANSPORT_GOOD;
}