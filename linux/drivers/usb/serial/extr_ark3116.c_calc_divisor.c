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

__attribute__((used)) static inline int calc_divisor(int bps)
{
	/* Original ark3116 made some exceptions in rounding here
	 * because windows did the same. Assume that is not really
	 * necessary.
	 * Crystal is 12MHz, probably because of USB, but we divide by 4?
	 */
	return (12000000 + 2*bps) / (4*bps);
}