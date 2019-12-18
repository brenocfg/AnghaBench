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
typedef  int uint8_t ;
struct ubi_device {int peb_count; int peb_size; int /*<<< orphan*/  mtd; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int UBI_IO_BITFLIPS ; 
 int /*<<< orphan*/  UBI_IO_RETRIES ; 
 int /*<<< orphan*/  dbg_gen (char*) ; 
 int /*<<< orphan*/  dbg_io (char*,int,int,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int mtd_read (int /*<<< orphan*/ ,int,int,size_t*,void*) ; 
 int self_check_not_bad (struct ubi_device const*,int) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 scalar_t__ ubi_dbg_is_bitflip (struct ubi_device const*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device const*,char*,int,char const*,int,int,int,size_t) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device const*,char*,int) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device const*,char*,int,char const*,int,int,int,size_t) ; 
 int /*<<< orphan*/  yield () ; 

int ubi_io_read(const struct ubi_device *ubi, void *buf, int pnum, int offset,
		int len)
{
	int err, retries = 0;
	size_t read;
	loff_t addr;

	dbg_io("read %d bytes from PEB %d:%d", len, pnum, offset);

	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);
	ubi_assert(offset >= 0 && offset + len <= ubi->peb_size);
	ubi_assert(len > 0);

	err = self_check_not_bad(ubi, pnum);
	if (err)
		return err;

	/*
	 * Deliberately corrupt the buffer to improve robustness. Indeed, if we
	 * do not do this, the following may happen:
	 * 1. The buffer contains data from previous operation, e.g., read from
	 *    another PEB previously. The data looks like expected, e.g., if we
	 *    just do not read anything and return - the caller would not
	 *    notice this. E.g., if we are reading a VID header, the buffer may
	 *    contain a valid VID header from another PEB.
	 * 2. The driver is buggy and returns us success or -EBADMSG or
	 *    -EUCLEAN, but it does not actually put any data to the buffer.
	 *
	 * This may confuse UBI or upper layers - they may think the buffer
	 * contains valid data while in fact it is just old data. This is
	 * especially possible because UBI (and UBIFS) relies on CRC, and
	 * treats data as correct even in case of ECC errors if the CRC is
	 * correct.
	 *
	 * Try to prevent this situation by changing the first byte of the
	 * buffer.
	 */
	*((uint8_t *)buf) ^= 0xFF;

	addr = (loff_t)pnum * ubi->peb_size + offset;
retry:
	err = mtd_read(ubi->mtd, addr, len, &read, buf);
	if (err) {
		const char *errstr = mtd_is_eccerr(err) ? " (ECC error)" : "";

		if (mtd_is_bitflip(err)) {
			/*
			 * -EUCLEAN is reported if there was a bit-flip which
			 * was corrected, so this is harmless.
			 *
			 * We do not report about it here unless debugging is
			 * enabled. A corresponding message will be printed
			 * later, when it is has been scrubbed.
			 */
			ubi_msg(ubi, "fixable bit-flip detected at PEB %d",
				pnum);
			ubi_assert(len == read);
			return UBI_IO_BITFLIPS;
		}

		if (retries++ < UBI_IO_RETRIES) {
			ubi_warn(ubi, "error %d%s while reading %d bytes from PEB %d:%d, read only %zd bytes, retry",
				 err, errstr, len, pnum, offset, read);
			yield();
			goto retry;
		}

		ubi_err(ubi, "error %d%s while reading %d bytes from PEB %d:%d, read %zd bytes",
			err, errstr, len, pnum, offset, read);
		dump_stack();

		/*
		 * The driver should never return -EBADMSG if it failed to read
		 * all the requested data. But some buggy drivers might do
		 * this, so we change it to -EIO.
		 */
		if (read != len && mtd_is_eccerr(err)) {
			ubi_assert(0);
			err = -EIO;
		}
	} else {
		ubi_assert(len == read);

		if (ubi_dbg_is_bitflip(ubi)) {
			dbg_gen("bit-flip (emulated)");
			err = UBI_IO_BITFLIPS;
		}
	}

	return err;
}