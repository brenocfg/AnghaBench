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
struct ubi_device {int peb_size; int /*<<< orphan*/  mtd; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 void* __vmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  mtd_is_bitflip (int) ; 
 int mtd_read (int /*<<< orphan*/ ,int,int,size_t*,void*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 
 int ubi_check_pattern (void*,int,int) ; 
 int /*<<< orphan*/  ubi_dbg_chk_io (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,...) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 

int ubi_self_check_all_ff(struct ubi_device *ubi, int pnum, int offset, int len)
{
	size_t read;
	int err;
	void *buf;
	loff_t addr = (loff_t)pnum * ubi->peb_size + offset;

	if (!ubi_dbg_chk_io(ubi))
		return 0;

	buf = __vmalloc(len, GFP_NOFS, PAGE_KERNEL);
	if (!buf) {
		ubi_err(ubi, "cannot allocate memory to check for 0xFFs");
		return 0;
	}

	err = mtd_read(ubi->mtd, addr, len, &read, buf);
	if (err && !mtd_is_bitflip(err)) {
		ubi_err(ubi, "err %d while reading %d bytes from PEB %d:%d, read %zd bytes",
			err, len, pnum, offset, read);
		goto error;
	}

	err = ubi_check_pattern(buf, 0xFF, len);
	if (err == 0) {
		ubi_err(ubi, "flash region at PEB %d:%d, length %d does not contain all 0xFF bytes",
			pnum, offset, len);
		goto fail;
	}

	vfree(buf);
	return 0;

fail:
	ubi_err(ubi, "self-check failed for PEB %d", pnum);
	ubi_msg(ubi, "hex dump of the %d-%d region", offset, offset + len);
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 1, buf, len, 1);
	err = -EINVAL;
error:
	dump_stack();
	vfree(buf);
	return err;
}