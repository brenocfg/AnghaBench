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
struct mtd_info {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read (struct mtd_info*,int /*<<< orphan*/ ,size_t,size_t*,void*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

int mtdtest_read(struct mtd_info *mtd, loff_t addr, size_t size, void *buf)
{
	size_t read;
	int err;

	err = mtd_read(mtd, addr, size, &read, buf);
	/* Ignore corrected ECC errors */
	if (mtd_is_bitflip(err))
		err = 0;
	if (!err && read != size)
		err = -EIO;
	if (err)
		pr_err("error: read failed at %#llx\n", addr);

	return err;
}