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
struct TYPE_3__ {int erasesize; int size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__* bbt ; 
 int ebcnt ; 
 int errcnt ; 
 unsigned char* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 TYPE_1__* mtd ; 
 int mtdtest_read (TYPE_1__*,int,int,unsigned char*) ; 
 int pgsize ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int crosstest(void)
{
	int err = 0, i;
	loff_t addr, addr0, addrn;
	unsigned char *pp1, *pp2, *pp3, *pp4;

	pr_info("crosstest\n");
	pp1 = kcalloc(pgsize, 4, GFP_KERNEL);
	if (!pp1)
		return -ENOMEM;
	pp2 = pp1 + pgsize;
	pp3 = pp2 + pgsize;
	pp4 = pp3 + pgsize;

	addr0 = 0;
	for (i = 0; i < ebcnt && bbt[i]; ++i)
		addr0 += mtd->erasesize;

	addrn = mtd->size;
	for (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addrn -= mtd->erasesize;

	/* Read 2nd-to-last page to pp1 */
	addr = addrn - pgsize - pgsize;
	err = mtdtest_read(mtd, addr, pgsize, pp1);
	if (err) {
		kfree(pp1);
		return err;
	}

	/* Read 3rd-to-last page to pp1 */
	addr = addrn - pgsize - pgsize - pgsize;
	err = mtdtest_read(mtd, addr, pgsize, pp1);
	if (err) {
		kfree(pp1);
		return err;
	}

	/* Read first page to pp2 */
	addr = addr0;
	pr_info("reading page at %#llx\n", (long long)addr);
	err = mtdtest_read(mtd, addr, pgsize, pp2);
	if (err) {
		kfree(pp1);
		return err;
	}

	/* Read last page to pp3 */
	addr = addrn - pgsize;
	pr_info("reading page at %#llx\n", (long long)addr);
	err = mtdtest_read(mtd, addr, pgsize, pp3);
	if (err) {
		kfree(pp1);
		return err;
	}

	/* Read first page again to pp4 */
	addr = addr0;
	pr_info("reading page at %#llx\n", (long long)addr);
	err = mtdtest_read(mtd, addr, pgsize, pp4);
	if (err) {
		kfree(pp1);
		return err;
	}

	/* pp2 and pp4 should be the same */
	pr_info("verifying pages read at %#llx match\n",
	       (long long)addr0);
	if (memcmp(pp2, pp4, pgsize)) {
		pr_err("verify failed!\n");
		errcnt += 1;
	} else if (!err)
		pr_info("crosstest ok\n");
	kfree(pp1);
	return err;
}