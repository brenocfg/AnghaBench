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
struct us_data {int /*<<< orphan*/  srb; scalar_t__ extra; } ;
struct sddr09_card_info {unsigned long blockshift; unsigned long blockmask; unsigned int capacity; unsigned int pageshift; unsigned int blocksize; unsigned int pagesize; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int CONTROL_SHIFT ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FROM_XFER_BUF ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int sddr09_write_lba (struct us_data*,unsigned int,unsigned int,unsigned int,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,unsigned int,int /*<<< orphan*/ ,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static int
sddr09_write_data(struct us_data *us,
		  unsigned long address,
		  unsigned int sectors) {

	struct sddr09_card_info *info = (struct sddr09_card_info *) us->extra;
	unsigned int lba, maxlba, page, pages;
	unsigned int pagelen, blocklen;
	unsigned char *blockbuffer;
	unsigned char *buffer;
	unsigned int len, offset;
	struct scatterlist *sg;
	int result;

	/* Figure out the initial LBA and page */
	lba = address >> info->blockshift;
	page = (address & info->blockmask);
	maxlba = info->capacity >> (info->pageshift + info->blockshift);
	if (lba >= maxlba)
		return -EIO;

	/*
	 * blockbuffer is used for reading in the old data, overwriting
	 * with the new data, and performing ECC calculations
	 */

	/*
	 * TODO: instead of doing kmalloc/kfree for each write,
	 * add a bufferpointer to the info structure
	 */

	pagelen = (1 << info->pageshift) + (1 << CONTROL_SHIFT);
	blocklen = (pagelen << info->blockshift);
	blockbuffer = kmalloc(blocklen, GFP_NOIO);
	if (!blockbuffer)
		return -ENOMEM;

	/*
	 * Since we don't write the user data directly to the device,
	 * we have to create a bounce buffer and move the data a piece
	 * at a time between the bounce buffer and the actual transfer buffer.
	 */

	len = min(sectors, (unsigned int) info->blocksize) * info->pagesize;
	buffer = kmalloc(len, GFP_NOIO);
	if (!buffer) {
		kfree(blockbuffer);
		return -ENOMEM;
	}

	result = 0;
	offset = 0;
	sg = NULL;

	while (sectors > 0) {

		/* Write as many sectors as possible in this block */

		pages = min(sectors, info->blocksize - page);
		len = (pages << info->pageshift);

		/* Not overflowing capacity? */
		if (lba >= maxlba) {
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, maxlba);
			result = -EIO;
			break;
		}

		/* Get the data from the transfer buffer */
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, FROM_XFER_BUF);

		result = sddr09_write_lba(us, lba, page, pages,
				buffer, blockbuffer);
		if (result)
			break;

		page = 0;
		lba++;
		sectors -= pages;
	}

	kfree(buffer);
	kfree(blockbuffer);

	return result;
}