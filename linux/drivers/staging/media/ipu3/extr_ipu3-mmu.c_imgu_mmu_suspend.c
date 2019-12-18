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
struct imgu_mmu_info {int dummy; } ;
struct imgu_mmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  imgu_mmu_set_halt (struct imgu_mmu*,int) ; 
 struct imgu_mmu* to_imgu_mmu (struct imgu_mmu_info*) ; 

void imgu_mmu_suspend(struct imgu_mmu_info *info)
{
	struct imgu_mmu *mmu = to_imgu_mmu(info);

	imgu_mmu_set_halt(mmu, true);
}