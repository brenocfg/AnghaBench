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

/* Variables and functions */
 int CFQ_SERVICE_SHIFT ; 
 int div_u64 (int,unsigned int) ; 

__attribute__((used)) static inline u64 cfqg_scale_charge(u64 charge,
				    unsigned int vfraction)
{
	u64 c = charge << CFQ_SERVICE_SHIFT;	/* make it fixed point */

	/* charge / vfraction */
	c <<= CFQ_SERVICE_SHIFT;
	return div_u64(c, vfraction);
}