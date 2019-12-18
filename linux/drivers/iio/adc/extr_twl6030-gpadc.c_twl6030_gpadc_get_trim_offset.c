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
typedef  int s8 ;
typedef  int __u32 ;

/* Variables and functions */
 int sign_extend32 (int,int) ; 

__attribute__((used)) static inline int twl6030_gpadc_get_trim_offset(s8 d)
{
	/*
	 * XXX NOTE!
	 * bit 0 - sign, bit 7 - reserved, 6..1 - trim value
	 * though, the documentation states that trim value
	 * is absolute value, the correct conversion results are
	 * obtained if the value is interpreted as 2's complement.
	 */
	__u32 temp = ((d & 0x7f) >> 1) | ((d & 1) << 6);

	return sign_extend32(temp, 6);
}