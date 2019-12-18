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
typedef  size_t uint32_t ;
typedef  int loff_t ;
struct TYPE_3__ {int erasesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_data (int /*<<< orphan*/ ,size_t) ; 
 int errcnt ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,size_t) ; 
 TYPE_1__* mtd ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read (TYPE_1__*,int,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long long) ; 
 int /*<<< orphan*/  pr_info (char*,long long) ; 
 int /*<<< orphan*/  readbuf ; 
 size_t subpgsize ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writebuf ; 

__attribute__((used)) static int verify_eraseblock_ff(int ebnum)
{
	uint32_t j;
	size_t read;
	int err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	memset(writebuf, 0xff, subpgsize);
	for (j = 0; j < mtd->erasesize / subpgsize; ++j) {
		clear_data(readbuf, subpgsize);
		err = mtd_read(mtd, addr, subpgsize, &read, readbuf);
		if (unlikely(err || read != subpgsize)) {
			if (mtd_is_bitflip(err) && read == subpgsize) {
				pr_info("ECC correction at %#llx\n",
				       (long long)addr);
				err = 0;
			} else {
				pr_err("error: read failed at "
				       "%#llx\n", (long long)addr);
				return err ? err : -1;
			}
		}
		if (unlikely(memcmp(readbuf, writebuf, subpgsize))) {
			pr_err("error: verify 0xff failed at "
			       "%#llx\n", (long long)addr);
			errcnt += 1;
		}
		addr += subpgsize;
	}

	return err;
}