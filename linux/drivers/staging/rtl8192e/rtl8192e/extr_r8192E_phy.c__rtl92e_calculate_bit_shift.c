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
 int ffs (int) ; 

__attribute__((used)) static u32 _rtl92e_calculate_bit_shift(u32 dwBitMask)
{
	if (!dwBitMask)
		return 32;
	return ffs(dwBitMask) - 1;
}