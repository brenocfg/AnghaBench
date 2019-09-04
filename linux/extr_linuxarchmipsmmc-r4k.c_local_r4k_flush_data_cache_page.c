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
 int /*<<< orphan*/  r4k_blast_dcache_page (unsigned long) ; 

__attribute__((used)) static inline void local_r4k_flush_data_cache_page(void * addr)
{
	r4k_blast_dcache_page((unsigned long) addr);
}