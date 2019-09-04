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
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mmu_context_ida ; 

void __destroy_context(int context_id)
{
	ida_free(&mmu_context_ida, context_id);
}