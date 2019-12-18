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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t *kfd_gtt_sa_calc_cpu_addr(void *start_addr,
						unsigned int bit_num,
						unsigned int chunk_size)
{
	return (uint32_t *) ((uint64_t) start_addr + bit_num * chunk_size);
}