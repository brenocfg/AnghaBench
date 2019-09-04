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
typedef  int u64 ;
typedef  int u32 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 adjust_tsc_khz(u32 khz, s32 ppm)
{
	u64 v = (u64)khz * (1000000 + ppm);
	do_div(v, 1000000);
	return v;
}