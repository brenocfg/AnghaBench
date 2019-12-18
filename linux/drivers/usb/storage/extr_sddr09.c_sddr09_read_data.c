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
struct sddr09_card_info {unsigned long blockshift; unsigned long blockmask; unsigned int capacity; unsigned int pageshift; unsigned int blocksize; unsigned int pagesize; unsigned int* lba_to_pba; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  TO_XFER_BUF ; 
 unsigned int UNDEF ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int sddr09_read20 (struct us_data*,unsigned long,unsigned int,unsigned int,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_access_xfer_buf (unsigned char*,unsigned int,int /*<<< orphan*/ ,struct scatterlist**,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,unsigned int,unsigned int,...) ; 

__attribute__((used)) static int
sddr09_read_data(struct us_data *us,
		 unsigned long address,
		 unsigned int sectors) {

	struct sddr09_card_info *info = (struct sddr09_card_info *) us->extra;
	unsigned char *buffer;
	unsigned int lba, maxlba, pba;
	unsigned int page, pages;
	unsigned int len, offset;
	struct scatterlist *sg;
	int result;

	// Figure out the initial LBA and page
	lba = address >> info->blockshift;
	page = (address & info->blockmask);
	maxlba = info->capacity >> (info->pageshift + info->blockshift);
	if (lba >= maxlba)
		return -EIO;

	// Since we only read in one block at a time, we have to create
	// a bounce buffer and move the data a piece at a time between the
	// bounce buffer and the actual transfer buffer.

	len = min(sectors, (unsigned int) info->blocksize) * info->pagesize;
	buffer = kmalloc(len, GFP_NOIO);
	if (!buffer)
		return -ENOMEM;

	// This could be made much more efficient by checking for
	// contiguous LBA's. Another exercise left to the student.

	result = 0;
	offset = 0;
	sg = NULL;

	while (sectors > 0) {

		/* Find number of pages we can read in this block */
		pages = min(sectors, info->blocksize - page);
		len = pages << info->pageshift;

		/* Not overflowing capacity? */
		if (lba >= maxlba) {
			usb_stor_dbg(us, "Error: Requested lba %u exceeds maximum %u\n",
				     lba, maxlba);
			result = -EIO;
			break;
		}

		/* Find where this lba lives on disk */
		pba = info->lba_to_pba[lba];

		if (pba == UNDEF) {	/* this lba was never written */

			usb_stor_dbg(us, "Read %d zero pages (LBA %d) page %d\n",
				     pages, lba, page);

			/*
			 * This is not really an error. It just means
			 * that the block has never been written.
			 * Instead of returning an error
			 * it is better to return all zero data.
			 */

			memset(buffer, 0, len);

		} else {
			usb_stor_dbg(us, "Read %d pages, from PBA %d (LBA %d) page %d\n",
				     pages, pba, lba, page);

			address = ((pba << info->blockshift) + page) << 
				info->pageshift;

			result = sddr09_read20(us, address>>1,
					pages, info->pageshift, buffer, 0);
			if (result)
				break;
		}

		// Store the data in the transfer buffer
		usb_stor_access_xfer_buf(buffer, len, us->srb,
				&sg, &offset, TO_XFER_BUF);

		page = 0;
		lba++;
		sectors -= pages;
	}

	kfree(buffer);
	return result;
}