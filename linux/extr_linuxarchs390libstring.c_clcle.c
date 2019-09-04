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

__attribute__((used)) static inline int clcle(const char *s1, unsigned long l1,
			const char *s2, unsigned long l2)
{
	register unsigned long r2 asm("2") = (unsigned long) s1;
	register unsigned long r3 asm("3") = (unsigned long) l1;
	register unsigned long r4 asm("4") = (unsigned long) s2;
	register unsigned long r5 asm("5") = (unsigned long) l2;
	int cc;

	asm volatile ("0: clcle %1,%3,0\n"
		      "   jo    0b\n"
		      "   ipm   %0\n"
		      "   srl   %0,28"
		      : "=&d" (cc), "+a" (r2), "+a" (r3),
			"+a" (r4), "+a" (r5) : : "cc", "memory");
	return cc;
}