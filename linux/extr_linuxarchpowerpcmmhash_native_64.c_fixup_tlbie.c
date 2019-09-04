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
 int /*<<< orphan*/  CPU_FTR_P9_TLBIE_BUG ; 
 int /*<<< orphan*/  ___tlbie (unsigned long,int,int,int) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void fixup_tlbie(unsigned long vpn, int psize, int apsize, int ssize)
{
	if (cpu_has_feature(CPU_FTR_P9_TLBIE_BUG)) {
		/* Need the extra ptesync to ensure we don't reorder tlbie*/
		asm volatile("ptesync": : :"memory");
		___tlbie(vpn, psize, apsize, ssize);
	}
}