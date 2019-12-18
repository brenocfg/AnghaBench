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
typedef  size_t u16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 scalar_t__ likely (int) ; 
 int* tid_to_ac ; 

__attribute__((used)) static inline int
il4965_get_ac_from_tid(u16 tid)
{
	if (likely(tid < ARRAY_SIZE(tid_to_ac)))
		return tid_to_ac[tid];

	/* no support for TIDs 8-15 yet */
	return -EINVAL;
}