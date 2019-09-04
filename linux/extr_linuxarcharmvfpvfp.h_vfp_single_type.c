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
struct vfp_single {int exponent; int significand; } ;

/* Variables and functions */
 int VFP_DENORMAL ; 
 int VFP_INFINITY ; 
 int VFP_NUMBER ; 
 int VFP_QNAN ; 
 int VFP_SINGLE_SIGNIFICAND_QNAN ; 
 int VFP_SNAN ; 
 int VFP_ZERO ; 

__attribute__((used)) static inline int vfp_single_type(struct vfp_single *s)
{
	int type = VFP_NUMBER;
	if (s->exponent == 255) {
		if (s->significand == 0)
			type = VFP_INFINITY;
		else if (s->significand & VFP_SINGLE_SIGNIFICAND_QNAN)
			type = VFP_QNAN;
		else
			type = VFP_SNAN;
	} else if (s->exponent == 0) {
		if (s->significand == 0)
			type |= VFP_ZERO;
		else
			type |= VFP_DENORMAL;
	}
	return type;
}