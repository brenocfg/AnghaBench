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
 int TX_DESC_RINGN_SIZE (int) ; 

__attribute__((used)) static inline int cas_intme(int ring, int entry)
{
	/* Algorithm: IRQ every 1/2 of descriptors. */
	if (!(entry & ((TX_DESC_RINGN_SIZE(ring) >> 1) - 1)))
		return 1;
	return 0;
}