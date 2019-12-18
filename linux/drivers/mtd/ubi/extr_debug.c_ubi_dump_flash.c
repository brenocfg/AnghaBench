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
 int EUCLEAN ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int mtd_read (int /*<<< orphan*/ ,int,int,size_t*,void*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 
 int /*<<< orphan*/  ubi_err (struct ubi_device*,char*,int,int,int,int,size_t) ; 
 int /*<<< orphan*/  ubi_msg (struct ubi_device*,char*,int,int,int) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc (int) ; 

void ubi_dump_flash(struct ubi_device *ubi, int pnum, int offset, int len)
{
	int err;
	size_t read;
	void *buf;
	loff_t addr = (loff_t)pnum * ubi->peb_size + offset;

	buf = vmalloc(len);
	if (!buf)
		return;
	err = mtd_read(ubi->mtd, addr, len, &read, buf);
	if (err && err != -EUCLEAN) {
		ubi_err(ubi, "err %d while reading %d bytes from PEB %d:%d, read %zd bytes",
			err, len, pnum, offset, read);
		goto out;
	}

	ubi_msg(ubi, "dumping %d bytes of data from PEB %d, offset %d",
		len, pnum, offset);
	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 32, 1, buf, len, 1);
out:
	vfree(buf);
	return;
}