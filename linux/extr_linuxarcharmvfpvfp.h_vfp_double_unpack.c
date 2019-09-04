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
struct vfp_double {int sign; int exponent; int significand; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int VFP_DOUBLE_MANTISSA_BITS ; 
 int vfp_double_packed_exponent (scalar_t__) ; 
 int vfp_double_packed_sign (scalar_t__) ; 

__attribute__((used)) static inline void vfp_double_unpack(struct vfp_double *s, s64 val)
{
	u64 significand;

	s->sign = vfp_double_packed_sign(val) >> 48;
	s->exponent = vfp_double_packed_exponent(val);

	significand = (u64) val;
	significand = (significand << (64 - VFP_DOUBLE_MANTISSA_BITS)) >> 2;
	if (s->exponent && s->exponent != 2047)
		significand |= (1ULL << 62);
	s->significand = significand;
}