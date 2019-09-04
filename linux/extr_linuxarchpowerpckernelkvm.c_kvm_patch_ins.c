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

/* Variables and functions */
 int /*<<< orphan*/  flush_icache_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void kvm_patch_ins(u32 *inst, u32 new_inst)
{
	*inst = new_inst;
	flush_icache_range((ulong)inst, (ulong)inst + 4);
}