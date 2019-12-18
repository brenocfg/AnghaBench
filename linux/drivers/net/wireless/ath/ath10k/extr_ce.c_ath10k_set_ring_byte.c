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
struct ath10k_hw_ce_regs_addr_map {unsigned int lsb; unsigned int mask; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int
ath10k_set_ring_byte(unsigned int offset,
		     struct ath10k_hw_ce_regs_addr_map *addr_map)
{
	return ((offset << addr_map->lsb) & addr_map->mask);
}