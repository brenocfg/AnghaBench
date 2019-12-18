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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 scalar_t__ CVMX_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  l2c_unlock_line (scalar_t__) ; 

__attribute__((used)) static void l2c_unlock_mem_region(u64 start, u64 len)
{
	u64 end;

	/* Round start/end to cache line boundaries */
	end = ALIGN(start + len - 1, CVMX_CACHE_LINE_SIZE);
	start = ALIGN(start, CVMX_CACHE_LINE_SIZE);

	while (start <= end) {
		l2c_unlock_line(start);
		start += CVMX_CACHE_LINE_SIZE;
	}
}