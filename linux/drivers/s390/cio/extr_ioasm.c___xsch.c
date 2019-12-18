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
struct subchannel_id {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int __xsch(struct subchannel_id schid)
{
	register struct subchannel_id reg1 asm("1") = schid;
	int ccode;

	asm volatile(
		"	xsch\n"
		"	ipm	%0\n"
		"	srl	%0,28"
		: "=d" (ccode)
		: "d" (reg1)
		: "cc");
	return ccode;
}