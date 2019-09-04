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
typedef  int uint32_t ;
struct rnd_state {int dummy; } ;
typedef  int loff_t ;
struct TYPE_3__ {int erasesize; int size; } ;

/* Variables and functions */
 scalar_t__* bbt ; 
 scalar_t__ boundary ; 
 int bufsize ; 
 int ebcnt ; 
 int errcnt ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mtd ; 
 int mtdtest_read (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int pgcnt ; 
 int pgsize ; 
 int /*<<< orphan*/  pr_err (char*,long long) ; 
 int /*<<< orphan*/  prandom_bytes_state (struct rnd_state*,scalar_t__,int) ; 
 struct rnd_state rnd_state ; 
 int /*<<< orphan*/  twopages ; 
 scalar_t__ writebuf ; 

__attribute__((used)) static int verify_eraseblock(int ebnum)
{
	uint32_t j;
	int err = 0, i;
	loff_t addr0, addrn;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	addr0 = 0;
	for (i = 0; i < ebcnt && bbt[i]; ++i)
		addr0 += mtd->erasesize;

	addrn = mtd->size;
	for (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addrn -= mtd->erasesize;

	prandom_bytes_state(&rnd_state, writebuf, mtd->erasesize);
	for (j = 0; j < pgcnt - 1; ++j, addr += pgsize) {
		/* Do a read to set the internal dataRAMs to different data */
		err = mtdtest_read(mtd, addr0, bufsize, twopages);
		if (err)
			return err;
		err = mtdtest_read(mtd, addrn - bufsize, bufsize, twopages);
		if (err)
			return err;
		memset(twopages, 0, bufsize);
		err = mtdtest_read(mtd, addr, bufsize, twopages);
		if (err)
			break;
		if (memcmp(twopages, writebuf + (j * pgsize), bufsize)) {
			pr_err("error: verify failed at %#llx\n",
			       (long long)addr);
			errcnt += 1;
		}
	}
	/* Check boundary between eraseblocks */
	if (addr <= addrn - pgsize - pgsize && !bbt[ebnum + 1]) {
		struct rnd_state old_state = rnd_state;

		/* Do a read to set the internal dataRAMs to different data */
		err = mtdtest_read(mtd, addr0, bufsize, twopages);
		if (err)
			return err;
		err = mtdtest_read(mtd, addrn - bufsize, bufsize, twopages);
		if (err)
			return err;
		memset(twopages, 0, bufsize);
		err = mtdtest_read(mtd, addr, bufsize, twopages);
		if (err)
			return err;
		memcpy(boundary, writebuf + mtd->erasesize - pgsize, pgsize);
		prandom_bytes_state(&rnd_state, boundary + pgsize, pgsize);
		if (memcmp(twopages, boundary, bufsize)) {
			pr_err("error: verify failed at %#llx\n",
			       (long long)addr);
			errcnt += 1;
		}
		rnd_state = old_state;
	}
	return err;
}