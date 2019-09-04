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
typedef  unsigned int u64 ;

/* Variables and functions */
 unsigned int EVENT_THR_CMP_MASK ; 
 unsigned int EVENT_THR_CMP_SHIFT ; 

__attribute__((used)) static bool is_thresh_cmp_valid(u64 event)
{
	unsigned int cmp, exp;

	/*
	 * Check the mantissa upper two bits are not zero, unless the
	 * exponent is also zero. See the THRESH_CMP_MANTISSA doc.
	 */
	cmp = (event >> EVENT_THR_CMP_SHIFT) & EVENT_THR_CMP_MASK;
	exp = cmp >> 7;

	if (exp && (cmp & 0x60) == 0)
		return false;

	return true;
}