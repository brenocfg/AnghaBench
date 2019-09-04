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
struct psb_mmu_pt {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct psb_mmu_pt*) ; 

__attribute__((used)) static void psb_mmu_free_pt(struct psb_mmu_pt *pt)
{
	__free_page(pt->p);
	kfree(pt);
}