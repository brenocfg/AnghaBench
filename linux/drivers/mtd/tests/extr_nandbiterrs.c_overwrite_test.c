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
typedef  int /*<<< orphan*/  bitstats ;
struct TYPE_2__ {unsigned int writesize; } ;

/* Variables and functions */
 int EIO ; 
 int MAXBITS ; 
 int /*<<< orphan*/  hash (scalar_t__) ; 
 unsigned int max_overwrite ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mtd ; 
 int mtdtest_relax () ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int read_page (int /*<<< orphan*/ ) ; 
 scalar_t__ seed ; 
 int verify_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wbuffer ; 
 int write_page (int) ; 

__attribute__((used)) static int overwrite_test(void)
{
	int err = 0;
	unsigned i;
	unsigned max_corrected = 0;
	unsigned opno = 0;
	/* We don't expect more than this many correctable bit errors per
	 * page. */
	#define MAXBITS 512
	static unsigned bitstats[MAXBITS]; /* bit error histogram. */

	memset(bitstats, 0, sizeof(bitstats));

	pr_info("overwrite biterrors test\n");

	for (i = 0; i < mtd->writesize; i++)
		wbuffer[i] = hash(i+seed);

	err = write_page(1);
	if (err)
		goto exit;

	while (opno < max_overwrite) {

		err = write_page(0);
		if (err)
			break;

		err = read_page(0);
		if (err >= 0) {
			if (err >= MAXBITS) {
				pr_info("Implausible number of bit errors corrected\n");
				err = -EIO;
				break;
			}
			bitstats[err]++;
			if (err > max_corrected) {
				max_corrected = err;
				pr_info("Read reported %d corrected bit errors\n",
					err);
			}
		} else { /* err < 0 */
			pr_info("Read reported error %d\n", err);
			err = 0;
			break;
		}

		err = verify_page(0);
		if (err) {
			bitstats[max_corrected] = opno;
			pr_info("ECC failure, read data is incorrect despite read success\n");
			break;
		}

		err = mtdtest_relax();
		if (err)
			break;

		opno++;
	}

	/* At this point bitstats[0] contains the number of ops with no bit
	 * errors, bitstats[1] the number of ops with 1 bit error, etc. */
	pr_info("Bit error histogram (%d operations total):\n", opno);
	for (i = 0; i < max_corrected; i++)
		pr_info("Page reads with %3d corrected bit errors: %d\n",
			i, bitstats[i]);

exit:
	return err;
}