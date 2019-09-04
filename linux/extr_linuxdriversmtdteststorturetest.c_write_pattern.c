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
 int EIO ; 
 TYPE_1__* mtd ; 
 int mtd_write (TYPE_1__*,int,size_t,size_t*,void*) ; 
 int pgcnt ; 
 int pgsize ; 
 int /*<<< orphan*/  pr_err (char*,int,int,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,size_t) ; 

__attribute__((used)) static inline int write_pattern(int ebnum, void *buf)
{
	int err;
	size_t written;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	size_t len = mtd->erasesize;

	if (pgcnt) {
		addr = (loff_t)(ebnum + 1) * mtd->erasesize - pgcnt * pgsize;
		len = pgcnt * pgsize;
	}
	err = mtd_write(mtd, addr, len, &written, buf);
	if (err) {
		pr_err("error %d while writing EB %d, written %zd"
		      " bytes\n", err, ebnum, written);
		return err;
	}
	if (written != len) {
		pr_info("written only %zd bytes of %zd, but no error"
		       " reported\n", written, len);
		return -EIO;
	}

	return 0;
}