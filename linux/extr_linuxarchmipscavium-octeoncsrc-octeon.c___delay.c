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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ read_c0_cvmcount () ; 

void __delay(unsigned long loops)
{
	u64 cur, end;

	cur = read_c0_cvmcount();
	end = cur + loops;

	while (end > cur)
		cur = read_c0_cvmcount();
}