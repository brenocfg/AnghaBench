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
typedef  unsigned int u16 ;
struct us_data {int /*<<< orphan*/  srb; } ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {unsigned int blockshift; unsigned int pageshift; unsigned int blocksize; unsigned int pagesize; unsigned long blockmask; unsigned int capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  FROM_XFER_BUF ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 TYPE_1__ MEDIA_INFO (struct us_data*) ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int alauda_write_lba (struct us_data*,unsigned int,unsigned int,unsigned int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned char* kmalloc_array (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,unsigned int,int /*<<< orphan*/ ,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int alauda_write_data(struct us_data *us, unsigned long address,
		unsigned int sectors)
{
	unsigned char *buffer, *blockbuffer;
	unsigned int page, len, offset;
	unsigned int blockshift = MEDIA_INFO(us).blockshift;
	unsigned int pageshift = MEDIA_INFO(us).pageshift;
	unsigned int blocksize = MEDIA_INFO(us).blocksize;
	unsigned int pagesize = MEDIA_INFO(us).pagesize;
	struct scatterlist *sg;
	u16 lba, max_lba;
	int result;

	/*
	 * Since we don't write the user data directly to the device,
	 * we have to create a bounce buffer and move the data a piece
	 * at a time between the bounce buffer and the actual transfer buffer.
	 */

	len = min(sectors, blocksize) * pagesize;
	buffer = kmalloc(len, GFP_NOIO);
	if (!buffer)
		return USB_STOR_TRANSPORT_ERROR;

	/*
	 * We also need a temporary block buffer, where we read in the old data,
	 * overwrite parts with the new data, and manipulate the redundancy data
	 */
	blockbuffer = kmalloc_array(pagesize + 64, blocksize, GFP_NOIO);
	if (!blockbuffer) {
		kfree(buffer);
		return USB_STOR_TRANSPORT_ERROR;
	}

	/* Figure out the initial LBA and page */
	lba = address >> blockshift;
	page = (address & MEDIA_INFO(us).blockmask);
	max_lba = MEDIA_INFO(us).capacity >> (pageshift + blockshift);

	result = USB_STOR_TRANSPORT_GOOD;
	offset = 0;
	sg = NULL;

	while (sectors > 0) {
		/* Write as many sectors as possible in this block */
		unsigned int pages = min(sectors, blocksize - page);
		len = pages << pageshift;

		/* Not overflowing capacity? */
		if (lba >= max_lba) {
			usb_stor_dbg(us, "Requested lba %u exceeds maximum %u\n",
				     lba, max_lba);
			result = USB_STOR_TRANSPORT_ERROR;
			break;
		}

		/* Get the data from the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, FROM_XFER_BUF);

		result = alauda_write_lba(us, lba, page, pages, buffer,
			blockbuffer);
		if (result != USB_STOR_TRANSPORT_GOOD)
			break;

		page = 0;
		lba++;
		sectors -= pages;
	}

	kfree(buffer);
	kfree(blockbuffer);
	return result;
}