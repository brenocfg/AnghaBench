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

__attribute__((used)) static inline int do_siga_input(unsigned long schid, unsigned int mask,
				unsigned int fc)
{
	register unsigned long __fc asm ("0") = fc;
	register unsigned long __schid asm ("1") = schid;
	register unsigned long __mask asm ("2") = mask;
	int cc;

	asm volatile(
		"	siga	0\n"
		"	ipm	%0\n"
		"	srl	%0,28\n"
		: "=d" (cc)
		: "d" (__fc), "d" (__schid), "d" (__mask) : "cc");
	return cc;
}