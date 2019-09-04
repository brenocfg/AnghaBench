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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int __xdiv64_32 (int,int) ; 

uint32_t __div64_32(u64 *xp, u32 y)
{
	uint32_t rem;
	uint64_t q = __xdiv64_32(*xp, y);

	rem = *xp - q * y;
	*xp = q;

	return rem;
}