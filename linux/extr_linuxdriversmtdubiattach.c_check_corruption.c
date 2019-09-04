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
struct ubi_vid_hdr {int dummy; } ;
struct ubi_device {int /*<<< orphan*/  buf_mutex; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  peb_buf; int /*<<< orphan*/  leb_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int UBI_IO_BITFLIPS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ubi_check_pattern (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubi_dbg_print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_dump_vid_hdr (struct ubi_vid_hdr*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int ubi_io_read (struct ubi_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_corruption(struct ubi_device *ubi, struct ubi_vid_hdr *vid_hdr,
			    int pnum)
{
	int err;

	mutex_lock(&ubi->buf_mutex);
	memset(ubi->peb_buf, 0x00, ubi->leb_size);

	err = ubi_io_read(ubi, ubi->peb_buf, pnum, ubi->leb_start,
			  ubi->leb_size);
	if (err == UBI_IO_BITFLIPS || mtd_is_eccerr(err)) {
		/*
		 * Bit-flips or integrity errors while reading the data area.
		 * It is difficult to say for sure what type of corruption is
		 * this, but presumably a power cut happened while this PEB was
		 * erased, so it became unstable and corrupted, and should be
		 * erased.
		 */
		err = 0;
		goto out_unlock;
	}

	if (err)
		goto out_unlock;

	if (ubi_check_pattern(ubi->peb_buf, 0xFF, ubi->leb_size))
		goto out_unlock;

	ubi_err(ubi, "PEB %d contains corrupted VID header, and the data does not contain all 0xFF",
		pnum);
	ubi_err(ubi, "this may be a non-UBI PEB or a severe VID header corruption which requires manual inspection");
	ubi_dump_vid_hdr(vid_hdr);
	pr_err("hexdump of PEB %d offset %d, length %d",
	       pnum, ubi->leb_start, ubi->leb_size);
	ubi_dbg_print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 1,
			       ubi->peb_buf, ubi->leb_size, 1);
	err = 1;

out_unlock:
	mutex_unlock(&ubi->buf_mutex);
	return err;
}