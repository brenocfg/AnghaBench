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
 int EINVAL ; 
 int EIO ; 
 int RETRIES ; 
 int /*<<< orphan*/  check_buf ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* mtd ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 int mtd_read (TYPE_1__*,int,size_t,size_t*,int /*<<< orphan*/ ) ; 
 int pgcnt ; 
 int pgsize ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  report_corrupt (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static inline int check_eraseblock(int ebnum, unsigned char *buf)
{
	int err, retries = 0;
	size_t read;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	size_t len = mtd->erasesize;

	if (pgcnt) {
		addr = (loff_t)(ebnum + 1) * mtd->erasesize - pgcnt * pgsize;
		len = pgcnt * pgsize;
	}

retry:
	err = mtd_read(mtd, addr, len, &read, check_buf);
	if (mtd_is_bitflip(err))
		pr_err("single bit flip occurred at EB %d "
		       "MTD reported that it was fixed.\n", ebnum);
	else if (err) {
		pr_err("error %d while reading EB %d, "
		       "read %zd\n", err, ebnum, read);
		return err;
	}

	if (read != len) {
		pr_err("failed to read %zd bytes from EB %d, "
		       "read only %zd, but no error reported\n",
		       len, ebnum, read);
		return -EIO;
	}

	if (memcmp(buf, check_buf, len)) {
		pr_err("read wrong data from EB %d\n", ebnum);
		report_corrupt(check_buf, buf);

		if (retries++ < RETRIES) {
			/* Try read again */
			yield();
			pr_info("re-try reading data from EB %d\n",
			       ebnum);
			goto retry;
		} else {
			pr_info("retried %d times, still errors, "
			       "give-up\n", RETRIES);
			return -EINVAL;
		}
	}

	if (retries != 0)
		pr_info("only attempt number %d was OK (!!!)\n",
		       retries);

	return 0;
}