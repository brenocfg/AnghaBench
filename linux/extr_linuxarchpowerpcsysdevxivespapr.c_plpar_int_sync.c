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

/* Variables and functions */
 int /*<<< orphan*/  H_INT_SYNC ; 
 scalar_t__ plpar_busy_delay (long) ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,long) ; 

__attribute__((used)) static long plpar_int_sync(unsigned long flags, unsigned long lisn)
{
	long rc;

	do {
		rc = plpar_hcall_norets(H_INT_SYNC, flags, lisn);
	} while (plpar_busy_delay(rc));

	if (rc) {
		pr_err("H_INT_SYNC lisn=%ld returned %ld\n", lisn, rc);
		return  rc;
	}

	return 0;
}