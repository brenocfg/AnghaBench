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
 int fpu_tag_word ; 
 int top ; 

void FPU_settag0(int tag)
{
	int regnr = top;
	regnr &= 7;
	fpu_tag_word &= ~(3 << (regnr * 2));
	fpu_tag_word |= (tag & 3) << (regnr * 2);
}