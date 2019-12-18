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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ HL_EQ_LENGTH ; 
 scalar_t__ unlikely (int) ; 

inline u32 hl_eq_inc_ptr(u32 ptr)
{
	ptr++;
	if (unlikely(ptr == HL_EQ_LENGTH))
		ptr = 0;
	return ptr;
}