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
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int /*<<< orphan*/  eprom_available; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_EPROM ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  EPROM_TIMEOUT ; 
 int EP_PAGE_DWORDS ; 
 scalar_t__ EP_PAGE_SIZE ; 
 scalar_t__ FOOTER_MAGIC ; 
 scalar_t__ SEG_SIZE ; 
 int acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_length (struct hfi1_devdata*,scalar_t__,scalar_t__,scalar_t__*) ; 
 int read_partition_platform_config (struct hfi1_devdata*,void**,scalar_t__*) ; 
 int read_segment_platform_config (struct hfi1_devdata*,scalar_t__*,void**,scalar_t__*) ; 
 int /*<<< orphan*/  release_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int eprom_read_platform_config(struct hfi1_devdata *dd, void **data, u32 *size)
{
	u32 directory[EP_PAGE_DWORDS]; /* aligned buffer */
	int ret;

	if (!dd->eprom_available)
		return -ENXIO;

	ret = acquire_chip_resource(dd, CR_EPROM, EPROM_TIMEOUT);
	if (ret)
		return -EBUSY;

	/* read the last page of the segment for the EPROM format magic */
	ret = read_length(dd, SEG_SIZE - EP_PAGE_SIZE, EP_PAGE_SIZE, directory);
	if (ret)
		goto done;

	/* last dword of the segment contains a magic value */
	if (directory[EP_PAGE_DWORDS - 1] == FOOTER_MAGIC) {
		/* segment format */
		ret = read_segment_platform_config(dd, directory, data, size);
	} else {
		/* partition format */
		ret = read_partition_platform_config(dd, data, size);
	}

done:
	release_chip_resource(dd, CR_EPROM);
	return ret;
}