#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int writesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash (scalar_t__) ; 
 int insert_biterror (unsigned int) ; 
 TYPE_1__* mtd ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int read_page (int) ; 
 int rewrite_page (int) ; 
 scalar_t__ seed ; 
 unsigned int subcount ; 
 unsigned int subsize ; 
 int verify_page (int) ; 
 int /*<<< orphan*/ * wbuffer ; 
 int write_page (int) ; 

__attribute__((used)) static int incremental_errors_test(void)
{
	int err = 0;
	unsigned i;
	unsigned errs_per_subpage = 0;

	pr_info("incremental biterrors test\n");

	for (i = 0; i < mtd->writesize; i++)
		wbuffer[i] = hash(i+seed);

	err = write_page(1);
	if (err)
		goto exit;

	while (1) {

		err = rewrite_page(1);
		if (err)
			goto exit;

		err = read_page(1);
		if (err > 0)
			pr_info("Read reported %d corrected bit errors\n", err);
		if (err < 0) {
			pr_err("After %d biterrors per subpage, read reported error %d\n",
				errs_per_subpage, err);
			err = 0;
			goto exit;
		}

		err = verify_page(1);
		if (err) {
			pr_err("ECC failure, read data is incorrect despite read success\n");
			goto exit;
		}

		pr_info("Successfully corrected %d bit errors per subpage\n",
			errs_per_subpage);

		for (i = 0; i < subcount; i++) {
			err = insert_biterror(i * subsize);
			if (err < 0)
				goto exit;
		}
		errs_per_subpage++;
	}

exit:
	return err;
}