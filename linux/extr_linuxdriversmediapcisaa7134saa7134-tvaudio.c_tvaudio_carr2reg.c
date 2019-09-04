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

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static u32 tvaudio_carr2reg(u32 carrier)
{
	u64 a = carrier;

	a <<= 24;
	do_div(a,12288);
	return a;
}