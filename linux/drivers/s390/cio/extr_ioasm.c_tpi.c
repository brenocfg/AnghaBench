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
struct tpi_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_s390_cio_tpi (struct tpi_info*,int) ; 

int tpi(struct tpi_info *addr)
{
	int ccode;

	asm volatile(
		"	tpi	0(%2)\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode), "=m" (*addr)
		: "a" (addr)
		: "cc");
	trace_s390_cio_tpi(addr, ccode);

	return ccode;
}