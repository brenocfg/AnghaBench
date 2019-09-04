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
struct ubi_device {int peb_count; int peb_size; int /*<<< orphan*/  mtd; scalar_t__ ro_mode; } ;
struct erase_info {int addr; int len; } ;
typedef  int loff_t ;

/* Variables and functions */
 int EIO ; 
 int EROFS ; 
 int /*<<< orphan*/  UBI_IO_RETRIES ; 
 int /*<<< orphan*/  dbg_io (char*,int) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  memset (struct erase_info*,int /*<<< orphan*/ ,int) ; 
 int mtd_erase (int /*<<< orphan*/ ,struct erase_info*) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 
 scalar_t__ ubi_dbg_is_erase_failure (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int ubi_self_check_all_ff (struct ubi_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ubi_warn (struct ubi_device*,char*,int,int) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int do_sync_erase(struct ubi_device *ubi, int pnum)
{
	int err, retries = 0;
	struct erase_info ei;

	dbg_io("erase PEB %d", pnum);
	ubi_assert(pnum >= 0 && pnum < ubi->peb_count);

	if (ubi->ro_mode) {
		ubi_err(ubi, "read-only mode");
		return -EROFS;
	}

retry:
	memset(&ei, 0, sizeof(struct erase_info));

	ei.addr     = (loff_t)pnum * ubi->peb_size;
	ei.len      = ubi->peb_size;

	err = mtd_erase(ubi->mtd, &ei);
	if (err) {
		if (retries++ < UBI_IO_RETRIES) {
			ubi_warn(ubi, "error %d while erasing PEB %d, retry",
				 err, pnum);
			yield();
			goto retry;
		}
		ubi_err(ubi, "cannot erase PEB %d, error %d", pnum, err);
		dump_stack();
		return err;
	}

	err = ubi_self_check_all_ff(ubi, pnum, 0, ubi->peb_size);
	if (err)
		return err;

	if (ubi_dbg_is_erase_failure(ubi)) {
		ubi_err(ubi, "cannot erase PEB %d (emulated)", pnum);
		return -EIO;
	}

	return 0;
}