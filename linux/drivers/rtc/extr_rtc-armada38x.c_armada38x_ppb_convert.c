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
 long div_s64 (long long,long) ; 

__attribute__((used)) static long armada38x_ppb_convert(long ppb)
{
	long div = ppb + 1000000000L;

	return div_s64(1000000000000000000LL + div / 2, div) - 1000000000L;
}