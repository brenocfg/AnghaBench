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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int CMD_SHIFT ; 
 int EINVAL ; 
 int EP_PAGE_DWORDS ; 
 scalar_t__ EP_PAGE_MASK ; 
 scalar_t__ EP_PAGE_SIZE ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  read_page (struct hfi1_devdata*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int read_length(struct hfi1_devdata *dd, u32 start, u32 len, void *dest)
{
	u32 buffer[EP_PAGE_DWORDS];
	u32 end;
	u32 start_offset;
	u32 read_start;
	u32 bytes;

	if (len == 0)
		return 0;

	end = start + len;

	/*
	 * Make sure the read range is not outside of the controller read
	 * command address range.  Note that '>' is correct below - the end
	 * of the range is OK if it stops at the limit, but no higher.
	 */
	if (end > (1 << CMD_SHIFT))
		return -EINVAL;

	/* read the first partial page */
	start_offset = start & EP_PAGE_MASK;
	if (start_offset) {
		/* partial starting page */

		/* align and read the page that contains the start */
		read_start = start & ~EP_PAGE_MASK;
		read_page(dd, read_start, buffer);

		/* the rest of the page is available data */
		bytes = EP_PAGE_SIZE - start_offset;

		if (len <= bytes) {
			/* end is within this page */
			memcpy(dest, (u8 *)buffer + start_offset, len);
			return 0;
		}

		memcpy(dest, (u8 *)buffer + start_offset, bytes);

		start += bytes;
		len -= bytes;
		dest += bytes;
	}
	/* start is now page aligned */

	/* read whole pages */
	while (len >= EP_PAGE_SIZE) {
		read_page(dd, start, buffer);
		memcpy(dest, buffer, EP_PAGE_SIZE);

		start += EP_PAGE_SIZE;
		len -= EP_PAGE_SIZE;
		dest += EP_PAGE_SIZE;
	}

	/* read the last partial page */
	if (len) {
		read_page(dd, start, buffer);
		memcpy(dest, buffer, len);
	}

	return 0;
}