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
typedef  int loff_t ;
struct TYPE_3__ {int erasesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_data (int /*<<< orphan*/ ,int) ; 
 int errcnt ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mtd ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read (TYPE_1__*,int,int,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long long) ; 
 int /*<<< orphan*/  pr_info (char*,long long) ; 
 int /*<<< orphan*/  prandom_bytes_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readbuf ; 
 int /*<<< orphan*/  rnd_state ; 
 int subpgsize ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writebuf ; 

__attribute__((used)) static int verify_eraseblock2(int ebnum)
{
	size_t read;
	int err = 0, k;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	for (k = 1; k < 33; ++k) {
		if (addr + (subpgsize * k) > (loff_t)(ebnum + 1) * mtd->erasesize)
			break;
		prandom_bytes_state(&rnd_state, writebuf, subpgsize * k);
		clear_data(readbuf, subpgsize * k);
		err = mtd_read(mtd, addr, subpgsize * k, &read, readbuf);
		if (unlikely(err || read != subpgsize * k)) {
			if (mtd_is_bitflip(err) && read == subpgsize * k) {
				pr_info("ECC correction at %#llx\n",
				       (long long)addr);
				err = 0;
			} else {
				pr_err("error: read failed at "
				       "%#llx\n", (long long)addr);
				return err ? err : -1;
			}
		}
		if (unlikely(memcmp(readbuf, writebuf, subpgsize * k))) {
			pr_err("error: verify failed at %#llx\n",
			       (long long)addr);
			errcnt += 1;
		}
		addr += subpgsize * k;
	}

	return err;
}