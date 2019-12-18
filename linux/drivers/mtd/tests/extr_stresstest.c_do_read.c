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
 scalar_t__* bbt ; 
 TYPE_1__* mtd ; 
 int mtdtest_read (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int rand_eb () ; 
 int rand_len (int) ; 
 int rand_offs () ; 
 int /*<<< orphan*/  readbuf ; 

__attribute__((used)) static int do_read(void)
{
	int eb = rand_eb();
	int offs = rand_offs();
	int len = rand_len(offs);
	loff_t addr;

	if (bbt[eb + 1]) {
		if (offs >= mtd->erasesize)
			offs -= mtd->erasesize;
		if (offs + len > mtd->erasesize)
			len = mtd->erasesize - offs;
	}
	addr = (loff_t)eb * mtd->erasesize + offs;
	return mtdtest_read(mtd, addr, len, readbuf);
}