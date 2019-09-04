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
 size_t SIZE_MAX ; 

__attribute__((used)) static inline size_t size_vstruct(size_t nelem, size_t elem_size, size_t base)
{
	if (elem_size && nelem > (SIZE_MAX - base) / elem_size)
		return 0;
	return base + nelem * elem_size;
}