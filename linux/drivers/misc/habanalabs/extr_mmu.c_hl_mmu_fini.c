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
struct hl_device {int /*<<< orphan*/  mmu_pgt_pool; int /*<<< orphan*/  mmu_shadow_hop0; int /*<<< orphan*/  mmu_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 

void hl_mmu_fini(struct hl_device *hdev)
{
	if (!hdev->mmu_enable)
		return;

	kvfree(hdev->mmu_shadow_hop0);
	gen_pool_destroy(hdev->mmu_pgt_pool);

	/* MMU H/W fini will be done in device hw_fini() */
}