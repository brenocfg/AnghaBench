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

/* Variables and functions */
 int min (unsigned int,int) ; 

__attribute__((used)) static inline int calc_interval(u8 fps, u32 n, u32 d)
{
	if (!n || !d)
		return 1;
	if (d == fps)
		return n;
	n *= fps;
	return min(15U, n / d + (n % d >= (fps >> 1)));
}