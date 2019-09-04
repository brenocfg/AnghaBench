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
typedef  int u8 ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void update_latch_offset(u8 *offset, int i)
{
	/* Fix inconsistent ITFromLatch25 bit mapping... */
	if (unlikely(*offset == 17))
		*offset = 24;
	/* Fix inconsistent ab8540 bit mapping... */
	if (unlikely(*offset == 16))
		*offset = 25;
	if ((i == 3) && (*offset >= 24))
		*offset += 2;
}