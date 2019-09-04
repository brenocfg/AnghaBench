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
 int DCSS_SEGEXT ; 
 int /*<<< orphan*/  DIAG_STAT_X064 ; 
 int dcss_set_subcodes () ; 
 int /*<<< orphan*/  diag_stat_inc (int /*<<< orphan*/ ) ; 
 int scode_set ; 

__attribute__((used)) static inline int
dcss_diag(int *func, void *parameter,
           unsigned long *ret1, unsigned long *ret2)
{
	unsigned long rx, ry;
	int rc;

	if (scode_set == 0) {
		rc = dcss_set_subcodes();
		if (rc < 0)
			return rc;
		scode_set = 1;
	}
	rx = (unsigned long) parameter;
	ry = (unsigned long) *func;

	/* 64-bit Diag x'64' new subcode, keep in 64-bit addressing mode */
	diag_stat_inc(DIAG_STAT_X064);
	if (*func > DCSS_SEGEXT)
		asm volatile(
			"	diag	%0,%1,0x64\n"
			"	ipm	%2\n"
			"	srl	%2,28\n"
			: "+d" (rx), "+d" (ry), "=d" (rc) : : "cc");
	/* 31-bit Diag x'64' old subcode, switch to 31-bit addressing mode */
	else
		asm volatile(
			"	sam31\n"
			"	diag	%0,%1,0x64\n"
			"	sam64\n"
			"	ipm	%2\n"
			"	srl	%2,28\n"
			: "+d" (rx), "+d" (ry), "=d" (rc) : : "cc");
	*ret1 = rx;
	*ret2 = ry;
	return rc;
}