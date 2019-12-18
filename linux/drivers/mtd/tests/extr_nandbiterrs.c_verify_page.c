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
 int EIO ; 
 scalar_t__ hash (scalar_t__) ; 
 TYPE_1__* mtd ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__* rbuffer ; 
 scalar_t__ seed ; 

__attribute__((used)) static int verify_page(int log)
{
	unsigned i, errs = 0;

	if (log)
		pr_info("verify_page\n");

	for (i = 0; i < mtd->writesize; i++) {
		if (rbuffer[i] != hash(i+seed)) {
			pr_err("Error: page offset %u, expected %02x, got %02x\n",
				i, hash(i+seed), rbuffer[i]);
			errs++;
		}
	}

	if (errs)
		return -EIO;
	else
		return 0;
}