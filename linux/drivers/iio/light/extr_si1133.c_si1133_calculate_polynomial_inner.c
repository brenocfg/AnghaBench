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
typedef  int u32 ;
typedef  int u16 ;
typedef  int s8 ;

/* Variables and functions */

__attribute__((used)) static int si1133_calculate_polynomial_inner(u32 input, u8 fraction, u16 mag,
					     s8 shift)
{
	return ((input << fraction) / mag) << shift;
}