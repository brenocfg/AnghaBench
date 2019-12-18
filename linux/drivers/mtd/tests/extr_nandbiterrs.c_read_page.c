#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtd_ecc_stats {int corrected; } ;
typedef  int /*<<< orphan*/  oldstats ;
struct TYPE_5__ {int corrected; } ;
struct TYPE_4__ {size_t writesize; TYPE_3__ ecc_stats; } ;

/* Variables and functions */
 int EIO ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  memcpy (struct mtd_ecc_stats*,TYPE_3__*,int) ; 
 TYPE_1__* mtd ; 
 int mtd_read (TYPE_1__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ offset ; 
 int /*<<< orphan*/  pr_err (char*,long long) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  rbuffer ; 

__attribute__((used)) static int read_page(int log)
{
	int err = 0;
	size_t read;
	struct mtd_ecc_stats oldstats;

	if (log)
		pr_info("read_page\n");

	/* Saving last mtd stats */
	memcpy(&oldstats, &mtd->ecc_stats, sizeof(oldstats));

	err = mtd_read(mtd, offset, mtd->writesize, &read, rbuffer);
	if (!err || err == -EUCLEAN)
		err = mtd->ecc_stats.corrected - oldstats.corrected;

	if (err < 0 || read != mtd->writesize) {
		pr_err("error: read failed at %#llx\n", (long long)offset);
		if (err >= 0)
			err = -EIO;
	}

	return err;
}