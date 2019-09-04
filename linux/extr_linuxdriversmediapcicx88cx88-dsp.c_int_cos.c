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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */
 int INT_PI ; 

__attribute__((used)) static s32 int_cos(u32 x)
{
	u32 t2, t4, t6, t8;
	s32 ret;
	u16 period = x / INT_PI;

	if (period % 2)
		return -int_cos(x - INT_PI);
	x = x % INT_PI;
	if (x > INT_PI / 2)
		return -int_cos(INT_PI / 2 - (x % (INT_PI / 2)));
	/*
	 * Now x is between 0 and INT_PI/2.
	 * To calculate cos(x) we use it's Taylor polinom.
	 */
	t2 = x * x / 32768 / 2;
	t4 = t2 * x / 32768 * x / 32768 / 3 / 4;
	t6 = t4 * x / 32768 * x / 32768 / 5 / 6;
	t8 = t6 * x / 32768 * x / 32768 / 7 / 8;
	ret = 32768 - t2 + t4 - t6 + t8;
	return ret;
}