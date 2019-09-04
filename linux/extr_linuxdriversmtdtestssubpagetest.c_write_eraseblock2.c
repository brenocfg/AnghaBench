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
 TYPE_1__* mtd ; 
 int mtd_write (TYPE_1__*,int,int,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 
 int /*<<< orphan*/  prandom_bytes_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rnd_state ; 
 int subpgsize ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writebuf ; 

__attribute__((used)) static int write_eraseblock2(int ebnum)
{
	size_t written;
	int err = 0, k;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	for (k = 1; k < 33; ++k) {
		if (addr + (subpgsize * k) > (loff_t)(ebnum + 1) * mtd->erasesize)
			break;
		prandom_bytes_state(&rnd_state, writebuf, subpgsize * k);
		err = mtd_write(mtd, addr, subpgsize * k, &written, writebuf);
		if (unlikely(err || written != subpgsize * k)) {
			pr_err("error: write failed at %#llx\n",
			       (long long)addr);
			if (written != subpgsize * k) {
				pr_err("  write size: %#x\n",
				       subpgsize * k);
				pr_err("  written: %#08zx\n",
				       written);
			}
			return err ? err : -1;
		}
		addr += subpgsize * k;
	}

	return err;
}