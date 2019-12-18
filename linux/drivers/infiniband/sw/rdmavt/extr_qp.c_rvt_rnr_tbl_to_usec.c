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
 unsigned long* ib_rvt_rnr_table ; 

unsigned long rvt_rnr_tbl_to_usec(u32 index)
{
	return ib_rvt_rnr_table[(index & IB_AETH_CREDIT_MASK)];
}