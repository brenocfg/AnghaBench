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
typedef  size_t u32 ;

/* Variables and functions */
 size_t IB_AETH_CREDIT_MASK ; 
 size_t IB_AETH_CREDIT_SHIFT ; 
 unsigned long* ib_rvt_rnr_table ; 

__attribute__((used)) static inline unsigned long rvt_aeth_to_usec(u32 aeth)
{
	return ib_rvt_rnr_table[(aeth >> IB_AETH_CREDIT_SHIFT) &
				  IB_AETH_CREDIT_MASK];
}