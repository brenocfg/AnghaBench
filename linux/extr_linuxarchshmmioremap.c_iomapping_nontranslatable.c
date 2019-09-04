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

__attribute__((used)) static inline int iomapping_nontranslatable(unsigned long offset)
{
#ifdef CONFIG_29BIT
	/*
	 * In 29-bit mode this includes the fixed P1/P2 areas, as well as
	 * parts of P3.
	 */
	if (PXSEG(offset) < P3SEG || offset >= P3_ADDR_MAX)
		return 1;
#endif

	return 0;
}