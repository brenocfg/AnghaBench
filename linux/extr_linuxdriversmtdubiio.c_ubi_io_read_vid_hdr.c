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
struct ubi_vid_io_buf {void* buffer; } ;
struct ubi_vid_hdr {int /*<<< orphan*/  hdr_crc; int /*<<< orphan*/  magic; } ;
struct ubi_device {int peb_count; scalar_t__ vid_hdr_shift; int /*<<< orphan*/  vid_hdr_aloffset; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 int UBI_IO_BAD_HDR ; 
 int UBI_IO_BAD_HDR_EBADMSG ; 
 int UBI_IO_BITFLIPS ; 
 int UBI_IO_FF ; 
 int UBI_IO_FF_BITFLIPS ; 
 scalar_t__ UBI_VID_HDR_MAGIC ; 
 scalar_t__ UBI_VID_HDR_SIZE ; 
 int /*<<< orphan*/  UBI_VID_HDR_SIZE_CRC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct ubi_vid_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_bld (char*,int,...) ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 scalar_t__ ubi_check_pattern (struct ubi_vid_hdr*,int,scalar_t__) ; 
 int /*<<< orphan*/  ubi_dump_vid_hdr (struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int) ; 
 struct ubi_vid_hdr* ubi_get_vid_hdr (struct ubi_vid_io_buf*) ; 
 int ubi_io_read (struct ubi_device*,void*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int,...) ; 
 int validate_vid_hdr (struct ubi_device*,struct ubi_vid_hdr*) ; 

int ubi_io_read_vid_hdr(struct ubi_device *ubi, int pnum,
			struct ubi_vid_io_buf *vidb, int verbose)
{
	int err, read_err;
	uint32_t crc, magic, hdr_crc;
	struct ubi_vid_hdr *vid_hdr = ubi_get_vid_hdr(vidb);
	void *p = vidb->buffer;

	dbg_io("read VID header from PEB %d", pnum);
	ubi_assert(pnum >= 0 &&  pnum < ubi->peb_count);

	read_err = ubi_io_read(ubi, p, pnum, ubi->vid_hdr_aloffset,
			  ubi->vid_hdr_shift + UBI_VID_HDR_SIZE);
	if (read_err && read_err != UBI_IO_BITFLIPS && !mtd_is_eccerr(read_err))
		return read_err;

	magic = be32_to_cpu(vid_hdr->magic);
	if (magic != UBI_VID_HDR_MAGIC) {
		if (mtd_is_eccerr(read_err))
			return UBI_IO_BAD_HDR_EBADMSG;

		if (ubi_check_pattern(vid_hdr, 0xFF, UBI_VID_HDR_SIZE)) {
			if (verbose)
				ubi_warn(ubi, "no VID header found at PEB %d, only 0xFF bytes",
					 pnum);
			dbg_bld("no VID header found at PEB %d, only 0xFF bytes",
				pnum);
			if (!read_err)
				return UBI_IO_FF;
			else
				return UBI_IO_FF_BITFLIPS;
		}

		if (verbose) {
			ubi_warn(ubi, "bad magic number at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_VID_HDR_MAGIC);
			ubi_dump_vid_hdr(vid_hdr);
		}
		dbg_bld("bad magic number at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_VID_HDR_MAGIC);
		return UBI_IO_BAD_HDR;
	}

	crc = crc32(UBI_CRC32_INIT, vid_hdr, UBI_VID_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(vid_hdr->hdr_crc);

	if (hdr_crc != crc) {
		if (verbose) {
			ubi_warn(ubi, "bad CRC at PEB %d, calculated %#08x, read %#08x",
				 pnum, crc, hdr_crc);
			ubi_dump_vid_hdr(vid_hdr);
		}
		dbg_bld("bad CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);
		if (!read_err)
			return UBI_IO_BAD_HDR;
		else
			return UBI_IO_BAD_HDR_EBADMSG;
	}

	err = validate_vid_hdr(ubi, vid_hdr);
	if (err) {
		ubi_err(ubi, "validation failed for PEB %d", pnum);
		return -EINVAL;
	}

	return read_err ? UBI_IO_BITFLIPS : 0;
}