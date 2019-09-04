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
typedef  int uint64_t ;

/* Variables and functions */
 int CVMX_CACHE_LINE_MASK ; 
 scalar_t__ CVMX_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  CVMX_DCACHE_INVALIDATE ; 
 int /*<<< orphan*/  READ_ONCE (char) ; 
 char* cvmx_phys_to_ptr (int) ; 

__attribute__((used)) static void fault_in(uint64_t addr, int len)
{
	char *ptr;

	/*
	 * Adjust addr and length so we get all cache lines even for
	 * small ranges spanning two cache lines.
	 */
	len += addr & CVMX_CACHE_LINE_MASK;
	addr &= ~CVMX_CACHE_LINE_MASK;
	ptr = cvmx_phys_to_ptr(addr);
	/*
	 * Invalidate L1 cache to make sure all loads result in data
	 * being in L2.
	 */
	CVMX_DCACHE_INVALIDATE;
	while (len > 0) {
		READ_ONCE(*ptr);
		len -= CVMX_CACHE_LINE_SIZE;
		ptr += CVMX_CACHE_LINE_SIZE;
	}
}