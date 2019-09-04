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

__attribute__((used)) static inline void out_le32(volatile unsigned *addr, int val)
{
	__asm__ __volatile__("stwbrx %1,0,%2; sync" : "=m" (*addr)
			     : "r" (val), "r" (addr));
}