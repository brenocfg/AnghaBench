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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 MT2063_fLO_FractionalTerm(u32 f_ref, u32 num, u32 denom)
{
	u32 t1 = (f_ref >> 14) * num;
	u32 term1 = t1 / denom;
	u32 loss = t1 % denom;
	u32 term2 =
	    (((f_ref & 0x00003FFF) * num + (loss << 14)) + (denom / 2)) / denom;
	return (term1 << 14) + term2;
}