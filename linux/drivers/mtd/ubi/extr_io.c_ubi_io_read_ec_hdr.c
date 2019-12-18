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
struct ubi_ec_hdr {int /*<<< orphan*/  hdr_crc; int /*<<< orphan*/  magic; } ;
struct ubi_device {int peb_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UBI_CRC32_INIT ; 
 scalar_t__ UBI_EC_HDR_MAGIC ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE ; 
 int /*<<< orphan*/  UBI_EC_HDR_SIZE_CRC ; 
 int UBI_IO_BAD_HDR ; 
 int UBI_IO_BAD_HDR_EBADMSG ; 
 int UBI_IO_BITFLIPS ; 
 int UBI_IO_FF ; 
 int UBI_IO_FF_BITFLIPS ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ crc32 (int /*<<< orphan*/ ,struct ubi_ec_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_bld (char*,int,...) ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 scalar_t__ ubi_check_pattern (struct ubi_ec_hdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_dump_ec_hdr (struct ubi_ec_hdr*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int) ; 
 int ubi_io_read (struct ubi_device*,struct ubi_ec_hdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int,...) ; 
 int validate_ec_hdr (struct ubi_device*,struct ubi_ec_hdr*) ; 

int ubi_io_read_ec_hdr(struct ubi_device *ubi, int pnum,
		       struct ubi_ec_hdr *ec_hdr, int verbose)
{
	int err, read_err;
	uint32_t crc, magic, hdr_crc;

	dbg_io("read EC header from PEB %d", pnum);
	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	read_err = ubi_io_read(ubi, ec_hdr, pnum, 0, UBI_EC_HDR_SIZE);
	if (read_err) {
		if (read_err != UBI_IO_BITFLIPS && !mtd_is_eccerr(read_err))
			return read_err;

		/*
		 * We read all the data, but either a correctable bit-flip
		 * occurred, or MTD reported a data integrity error
		 * (uncorrectable ECC error in case of NAND). The former is
		 * harmless, the later may mean that the read data is
		 * corrupted. But we have a CRC check-sum and we will detect
		 * this. If the EC header is still OK, we just report this as
		 * there was a bit-flip, to force scrubbing.
		 */
	}

	magic = be32_to_cpu(ec_hdr->magic);
	if (magic != UBI_EC_HDR_MAGIC) {
		if (mtd_is_eccerr(read_err))
			return UBI_IO_BAD_HDR_EBADMSG;

		/*
		 * The magic field is wrong. Let's check if we have read all
		 * 0xFF. If yes, this physical eraseblock is assumed to be
		 * empty.
		 */
		if (ubi_check_pattern(ec_hdr, 0xFF, UBI_EC_HDR_SIZE)) {
			/* The physical eraseblock is supposedly empty */
			if (verbose)
				ubi_warn(ubi, "no EC header found at PEB %d, only 0xFF bytes",
					 pnum);
			dbg_bld("no EC header found at PEB %d, only 0xFF bytes",
				pnum);
			if (!read_err)
				return UBI_IO_FF;
			else
				return UBI_IO_FF_BITFLIPS;
		}

		/*
		 * This is not a valid erase counter header, and these are not
		 * 0xFF bytes. Report that the header is corrupted.
		 */
		if (verbose) {
			ubi_warn(ubi, "bad magic number at PEB %d: %08x instead of %08x",
				 pnum, magic, UBI_EC_HDR_MAGIC);
			ubi_dump_ec_hdr(ec_hdr);
		}
		dbg_bld("bad magic number at PEB %d: %08x instead of %08x",
			pnum, magic, UBI_EC_HDR_MAGIC);
		return UBI_IO_BAD_HDR;
	}

	crc = crc32(UBI_CRC32_INIT, ec_hdr, UBI_EC_HDR_SIZE_CRC);
	hdr_crc = be32_to_cpu(ec_hdr->hdr_crc);

	if (hdr_crc != crc) {
		if (verbose) {
			ubi_warn(ubi, "bad EC header CRC at PEB %d, calculated %#08x, read %#08x",
				 pnum, crc, hdr_crc);
			ubi_dump_ec_hdr(ec_hdr);
		}
		dbg_bld("bad EC header CRC at PEB %d, calculated %#08x, read %#08x",
			pnum, crc, hdr_crc);

		if (!read_err)
			return UBI_IO_BAD_HDR;
		else
			return UBI_IO_BAD_HDR_EBADMSG;
	}

	/* And of course validate what has just been read from the media */
	err = validate_ec_hdr(ubi, ec_hdr);
	if (err) {
		ubi_err(ubi, "validation failed for PEB %d", pnum);
		return -EINVAL;
	}

	/*
	 * If there was %-EBADMSG, but the header CRC is still OK, report about
	 * a bit-flip to force scrubbing on this PEB.
	 */
	return read_err ? UBI_IO_BITFLIPS : 0;
}