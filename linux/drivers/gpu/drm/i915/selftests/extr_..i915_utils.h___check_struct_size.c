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

/* Variables and functions */
 scalar_t__ check_add_overflow (size_t,size_t,size_t*) ; 
 scalar_t__ check_mul_overflow (size_t,size_t,size_t*) ; 

__attribute__((used)) static inline bool
__check_struct_size(size_t base, size_t arr, size_t count, size_t *size)
{
	size_t sz;

	if (check_mul_overflow(count, arr, &sz))
		return false;

	if (check_add_overflow(sz, base, &sz))
		return false;

	*size = sz;
	return true;
}