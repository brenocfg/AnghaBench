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
typedef  scalar_t__ uint32_t ;
struct ubi_vid_io_buf {int dummy; } ;
struct ubi_vid_hdr {int dummy; } ;
struct ubi_ec_hdr {int dummy; } ;
struct ubi_device {int peb_size; int /*<<< orphan*/  mtd; scalar_t__ vid_hdr_aloffset; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int UBI_IO_BAD_HDR ; 
 int UBI_IO_BAD_HDR_EBADMSG ; 
 int UBI_IO_FF ; 
 int mtd_write (int /*<<< orphan*/ ,int,int,size_t*,void*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_dump_flash (struct ubi_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int,int) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int /*<<< orphan*/  ubi_init_vid_buf (struct ubi_device*,struct ubi_vid_io_buf*,struct ubi_vid_hdr*) ; 
 int ubi_io_read_ec_hdr (struct ubi_device*,int,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 
 int ubi_io_read_vid_hdr (struct ubi_device*,int,struct ubi_vid_io_buf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nor_erase_prepare(struct ubi_device *ubi, int pnum)
{
	int err;
	size_t written;
	loff_t addr;
	uint32_t data = 0;
	struct ubi_ec_hdr ec_hdr;
	struct ubi_vid_io_buf vidb;

	/*
	 * Note, we cannot generally define VID header buffers on stack,
	 * because of the way we deal with these buffers (see the header
	 * comment in this file). But we know this is a NOR-specific piece of
	 * code, so we can do this. But yes, this is error-prone and we should
	 * (pre-)allocate VID header buffer instead.
	 */
	struct ubi_vid_hdr vid_hdr;

	/*
	 * If VID or EC is valid, we have to corrupt them before erasing.
	 * It is important to first invalidate the EC header, and then the VID
	 * header. Otherwise a power cut may lead to valid EC header and
	 * invalid VID header, in which case UBI will treat this PEB as
	 * corrupted and will try to preserve it, and print scary warnings.
	 */
	addr = (loff_t)pnum * ubi->peb_size;
	err = ubi_io_read_ec_hdr(ubi, pnum, &ec_hdr, 0);
	if (err != UBI_IO_BAD_HDR_EBADMSG && err != UBI_IO_BAD_HDR &&
	    err != UBI_IO_FF){
		err = mtd_write(ubi->mtd, addr, 4, &written, (void *)&data);
		if(err)
			goto error;
	}

	ubi_init_vid_buf(ubi, &vidb, &vid_hdr);
	ubi_assert(&vid_hdr == ubi_get_vid_hdr(&vidb));

	err = ubi_io_read_vid_hdr(ubi, pnum, &vidb, 0);
	if (err != UBI_IO_BAD_HDR_EBADMSG && err != UBI_IO_BAD_HDR &&
	    err != UBI_IO_FF){
		addr += ubi->vid_hdr_aloffset;
		err = mtd_write(ubi->mtd, addr, 4, &written, (void *)&data);
		if (err)
			goto error;
	}
	return 0;

error:
	/*
	 * The PEB contains a valid VID or EC header, but we cannot invalidate
	 * it. Supposedly the flash media or the driver is screwed up, so
	 * return an error.
	 */
	ubi_err(ubi, "cannot invalidate PEB %d, write returned %d", pnum, err);
	ubi_dump_flash(ubi, pnum, 0, ubi->peb_size);
	return -EIO;
}