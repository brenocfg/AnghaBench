#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ loff_t ;
struct TYPE_5__ {scalar_t__ erasesize; } ;

/* Variables and functions */
 scalar_t__* bbt ; 
 int ebcnt ; 
 int errcnt ; 
 TYPE_1__* mtd ; 
 int mtdtest_erase_eraseblock (TYPE_1__*,int) ; 
 int mtdtest_read (TYPE_1__*,scalar_t__,int,int*) ; 
 int mtdtest_write (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int pgsize ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  prandom_bytes_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rnd_state ; 
 int* twopages ; 
 int /*<<< orphan*/  writebuf ; 

__attribute__((used)) static int erasetest(void)
{
	int err = 0, i, ebnum, ok = 1;
	loff_t addr0;

	pr_info("erasetest\n");

	ebnum = 0;
	addr0 = 0;
	for (i = 0; i < ebcnt && bbt[i]; ++i) {
		addr0 += mtd->erasesize;
		ebnum += 1;
	}

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	if (err)
		return err;

	pr_info("writing 1st page of block %d\n", ebnum);
	prandom_bytes_state(&rnd_state, writebuf, pgsize);
	err = mtdtest_write(mtd, addr0, pgsize, writebuf);
	if (err)
		return err;

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	if (err)
		return err;

	pr_info("reading 1st page of block %d\n", ebnum);
	err = mtdtest_read(mtd, addr0, pgsize, twopages);
	if (err)
		return err;

	pr_info("verifying 1st page of block %d is all 0xff\n",
	       ebnum);
	for (i = 0; i < pgsize; ++i)
		if (twopages[i] != 0xff) {
			pr_err("verifying all 0xff failed at %d\n",
			       i);
			errcnt += 1;
			ok = 0;
			break;
		}

	if (ok && !err)
		pr_info("erasetest ok\n");

	return err;
}