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
typedef  scalar_t__ ulong ;
typedef  int /*<<< orphan*/  u32 ;
struct epapr_spin_table {int /*<<< orphan*/  addr_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  in_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 read_spin_table_addr_l(void *spin_table)
{
	flush_dcache_range((ulong)spin_table,
		(ulong)spin_table + sizeof(struct epapr_spin_table));
	return in_be32(&((struct epapr_spin_table *)spin_table)->addr_l);
}