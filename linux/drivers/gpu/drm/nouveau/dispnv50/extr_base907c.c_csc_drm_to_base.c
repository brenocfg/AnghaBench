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
 int BIT_ULL (int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32
csc_drm_to_base(u64 in)
{
	/* base takes a 19-bit 2's complement value in S3.16 format */
	bool sign = in & BIT_ULL(63);
	u32 integer = (in >> 32) & 0x7fffffff;
	u32 fraction = in & 0xffffffff;

	if (integer >= 4) {
		return (1 << 18) - (sign ? 0 : 1);
	} else {
		u32 ret = (integer << 16) | (fraction >> 16);
		if (sign)
			ret = -ret;
		return ret & GENMASK(18, 0);
	}
}