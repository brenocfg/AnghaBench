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
struct vfp_single {int sign; int exponent; int significand; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int VFP_SINGLE_MANTISSA_BITS ; 
 int vfp_single_packed_exponent (scalar_t__) ; 
 int vfp_single_packed_sign (scalar_t__) ; 

__attribute__((used)) static inline void vfp_single_unpack(struct vfp_single *s, s32 val)
{
	u32 significand;

	s->sign = vfp_single_packed_sign(val) >> 16,
	s->exponent = vfp_single_packed_exponent(val);

	significand = (u32) val;
	significand = (significand << (32 - VFP_SINGLE_MANTISSA_BITS)) >> 2;
	if (s->exponent && s->exponent != 255)
		significand |= 0x40000000;
	s->significand = significand;
}