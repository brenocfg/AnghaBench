#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubi_wl_entry {int dummy; } ;
struct ubi_device {int vid_hdr_offset; int peb_size; int peb_count; int bad_allowed; int nor_flash; int min_io_size; int hdrs_min_io_size; int max_write_size; int ec_hdr_alsize; int vid_hdr_alsize; int vid_hdr_aloffset; int vid_hdr_shift; int leb_start; int max_erroneous; int ro_mode; int leb_size; TYPE_1__* mtd; int /*<<< orphan*/  bad_peb_limit; int /*<<< orphan*/  flash_size; } ;
struct ubi_ainf_peb {int dummy; } ;
struct TYPE_3__ {scalar_t__ numeraseregions; int erasesize; scalar_t__ type; int writesize; int subpage_sft; int writebufsize; int flags; int /*<<< orphan*/  index; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 void* ALIGN (int,int) ; 
 int EINVAL ; 
 scalar_t__ MTD_NORFLASH ; 
 int MTD_WRITEABLE ; 
 int UBI_EC_HDR_SIZE ; 
 int UBI_VID_HDR_SIZE ; 
 int /*<<< orphan*/  dbg_gen (char*,int) ; 
 int /*<<< orphan*/  get_bad_peb_limit (struct ubi_device*,int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 scalar_t__ mtd_can_have_bb (TYPE_1__*) ; 
 int mtd_div_by_eb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*) ; 

__attribute__((used)) static int io_init(struct ubi_device *ubi, int max_beb_per1024)
{
	dbg_gen("sizeof(struct ubi_ainf_peb) %zu", sizeof(struct ubi_ainf_peb));
	dbg_gen("sizeof(struct ubi_wl_entry) %zu", sizeof(struct ubi_wl_entry));

	if (ubi->mtd->numeraseregions != 0) {
		/*
		 * Some flashes have several erase regions. Different regions
		 * may have different eraseblock size and other
		 * characteristics. It looks like mostly multi-region flashes
		 * have one "main" region and one or more small regions to
		 * store boot loader code or boot parameters or whatever. I
		 * guess we should just pick the largest region. But this is
		 * not implemented.
		 */
		ubi_err(ubi, "multiple regions, not implemented");
		return -EINVAL;
	}

	if (ubi->vid_hdr_offset < 0)
		return -EINVAL;

	/*
	 * Note, in this implementation we support MTD devices with 0x7FFFFFFF
	 * physical eraseblocks maximum.
	 */

	ubi->peb_size   = ubi->mtd->erasesize;
	ubi->peb_count  = mtd_div_by_eb(ubi->mtd->size, ubi->mtd);
	ubi->flash_size = ubi->mtd->size;

	if (mtd_can_have_bb(ubi->mtd)) {
		ubi->bad_allowed = 1;
		ubi->bad_peb_limit = get_bad_peb_limit(ubi, max_beb_per1024);
	}

	if (ubi->mtd->type == MTD_NORFLASH) {
		ubi_assert(ubi->mtd->writesize == 1);
		ubi->nor_flash = 1;
	}

	ubi->min_io_size = ubi->mtd->writesize;
	ubi->hdrs_min_io_size = ubi->mtd->writesize >> ubi->mtd->subpage_sft;

	/*
	 * Make sure minimal I/O unit is power of 2. Note, there is no
	 * fundamental reason for this assumption. It is just an optimization
	 * which allows us to avoid costly division operations.
	 */
	if (!is_power_of_2(ubi->min_io_size)) {
		ubi_err(ubi, "min. I/O unit (%d) is not power of 2",
			ubi->min_io_size);
		return -EINVAL;
	}

	ubi_assert(ubi->hdrs_min_io_size > 0);
	ubi_assert(ubi->hdrs_min_io_size <= ubi->min_io_size);
	ubi_assert(ubi->min_io_size % ubi->hdrs_min_io_size == 0);

	ubi->max_write_size = ubi->mtd->writebufsize;
	/*
	 * Maximum write size has to be greater or equivalent to min. I/O
	 * size, and be multiple of min. I/O size.
	 */
	if (ubi->max_write_size < ubi->min_io_size ||
	    ubi->max_write_size % ubi->min_io_size ||
	    !is_power_of_2(ubi->max_write_size)) {
		ubi_err(ubi, "bad write buffer size %d for %d min. I/O unit",
			ubi->max_write_size, ubi->min_io_size);
		return -EINVAL;
	}

	/* Calculate default aligned sizes of EC and VID headers */
	ubi->ec_hdr_alsize = ALIGN(UBI_EC_HDR_SIZE, ubi->hdrs_min_io_size);
	ubi->vid_hdr_alsize = ALIGN(UBI_VID_HDR_SIZE, ubi->hdrs_min_io_size);

	dbg_gen("min_io_size      %d", ubi->min_io_size);
	dbg_gen("max_write_size   %d", ubi->max_write_size);
	dbg_gen("hdrs_min_io_size %d", ubi->hdrs_min_io_size);
	dbg_gen("ec_hdr_alsize    %d", ubi->ec_hdr_alsize);
	dbg_gen("vid_hdr_alsize   %d", ubi->vid_hdr_alsize);

	if (ubi->vid_hdr_offset == 0)
		/* Default offset */
		ubi->vid_hdr_offset = ubi->vid_hdr_aloffset =
				      ubi->ec_hdr_alsize;
	else {
		ubi->vid_hdr_aloffset = ubi->vid_hdr_offset &
						~(ubi->hdrs_min_io_size - 1);
		ubi->vid_hdr_shift = ubi->vid_hdr_offset -
						ubi->vid_hdr_aloffset;
	}

	/* Similar for the data offset */
	ubi->leb_start = ubi->vid_hdr_offset + UBI_VID_HDR_SIZE;
	ubi->leb_start = ALIGN(ubi->leb_start, ubi->min_io_size);

	dbg_gen("vid_hdr_offset   %d", ubi->vid_hdr_offset);
	dbg_gen("vid_hdr_aloffset %d", ubi->vid_hdr_aloffset);
	dbg_gen("vid_hdr_shift    %d", ubi->vid_hdr_shift);
	dbg_gen("leb_start        %d", ubi->leb_start);

	/* The shift must be aligned to 32-bit boundary */
	if (ubi->vid_hdr_shift % 4) {
		ubi_err(ubi, "unaligned VID header shift %d",
			ubi->vid_hdr_shift);
		return -EINVAL;
	}

	/* Check sanity */
	if (ubi->vid_hdr_offset < UBI_EC_HDR_SIZE ||
	    ubi->leb_start < ubi->vid_hdr_offset + UBI_VID_HDR_SIZE ||
	    ubi->leb_start > ubi->peb_size - UBI_VID_HDR_SIZE ||
	    ubi->leb_start & (ubi->min_io_size - 1)) {
		ubi_err(ubi, "bad VID header (%d) or data offsets (%d)",
			ubi->vid_hdr_offset, ubi->leb_start);
		return -EINVAL;
	}

	/*
	 * Set maximum amount of physical erroneous eraseblocks to be 10%.
	 * Erroneous PEB are those which have read errors.
	 */
	ubi->max_erroneous = ubi->peb_count / 10;
	if (ubi->max_erroneous < 16)
		ubi->max_erroneous = 16;
	dbg_gen("max_erroneous    %d", ubi->max_erroneous);

	/*
	 * It may happen that EC and VID headers are situated in one minimal
	 * I/O unit. In this case we can only accept this UBI image in
	 * read-only mode.
	 */
	if (ubi->vid_hdr_offset + UBI_VID_HDR_SIZE <= ubi->hdrs_min_io_size) {
		ubi_warn(ubi, "EC and VID headers are in the same minimal I/O unit, switch to read-only mode");
		ubi->ro_mode = 1;
	}

	ubi->leb_size = ubi->peb_size - ubi->leb_start;

	if (!(ubi->mtd->flags & MTD_WRITEABLE)) {
		ubi_msg(ubi, "MTD device %d is write-protected, attach in read-only mode",
			ubi->mtd->index);
		ubi->ro_mode = 1;
	}

	/*
	 * Note, ideally, we have to initialize @ubi->bad_peb_count here. But
	 * unfortunately, MTD does not provide this information. We should loop
	 * over all physical eraseblocks and invoke mtd->block_is_bad() for
	 * each physical eraseblock. So, we leave @ubi->bad_peb_count
	 * uninitialized so far.
	 */

	return 0;
}