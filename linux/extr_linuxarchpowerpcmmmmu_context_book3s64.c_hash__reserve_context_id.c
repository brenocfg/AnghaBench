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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN (int,char*,int,int) ; 
 int ida_alloc_range (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_context_ida ; 

void hash__reserve_context_id(int id)
{
	int result = ida_alloc_range(&mmu_context_ida, id, id, GFP_KERNEL);

	WARN(result != id, "mmu: Failed to reserve context id %d (rc %d)\n", id, result);
}