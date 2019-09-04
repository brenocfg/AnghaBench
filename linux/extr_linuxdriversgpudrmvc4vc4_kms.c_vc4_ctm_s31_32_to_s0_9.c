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
typedef  int u16 ;

/* Variables and functions */
 int BIT (int) ; 
 int BIT_ULL (int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int GENMASK_ULL (int,int) ; 

__attribute__((used)) static u16 vc4_ctm_s31_32_to_s0_9(u64 in)
{
	u16 r;

	/* Sign bit. */
	r = in & BIT_ULL(63) ? BIT(9) : 0;

	if ((in & GENMASK_ULL(62, 32)) > 0) {
		/* We have zero integer bits so we can only saturate here. */
		r |= GENMASK(8, 0);
	} else {
		/* Otherwise take the 9 most important fractional bits. */
		r |= (in >> 23) & GENMASK(8, 0);
	}

	return r;
}