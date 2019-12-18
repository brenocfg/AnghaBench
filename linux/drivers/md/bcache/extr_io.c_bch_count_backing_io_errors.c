#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cached_dev {unsigned int error_limit; int /*<<< orphan*/  backing_dev_name; int /*<<< orphan*/  io_errors; } ;
struct bio {int bi_opf; } ;

/* Variables and functions */
 int REQ_RAHEAD ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 unsigned int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_cached_dev_error (struct cached_dev*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 

void bch_count_backing_io_errors(struct cached_dev *dc, struct bio *bio)
{
	unsigned int errors;

	WARN_ONCE(!dc, "NULL pointer of struct cached_dev");

	/*
	 * Read-ahead requests on a degrading and recovering md raid
	 * (e.g. raid6) device might be failured immediately by md
	 * raid code, which is not a real hardware media failure. So
	 * we shouldn't count failed REQ_RAHEAD bio to dc->io_errors.
	 */
	if (bio->bi_opf & REQ_RAHEAD) {
		pr_warn_ratelimited("%s: Read-ahead I/O failed on backing device, ignore",
				    dc->backing_dev_name);
		return;
	}

	errors = atomic_add_return(1, &dc->io_errors);
	if (errors < dc->error_limit)
		pr_err("%s: IO error on backing device, unrecoverable",
			dc->backing_dev_name);
	else
		bch_cached_dev_error(dc);
}