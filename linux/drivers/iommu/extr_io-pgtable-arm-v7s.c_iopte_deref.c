#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cfg; } ;
struct arm_v7s_io_pgtable {TYPE_1__ iop; } ;
typedef  int /*<<< orphan*/  arm_v7s_iopte ;

/* Variables and functions */
 int /*<<< orphan*/  iopte_to_paddr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static arm_v7s_iopte *iopte_deref(arm_v7s_iopte pte, int lvl,
				  struct arm_v7s_io_pgtable *data)
{
	return phys_to_virt(iopte_to_paddr(pte, lvl, &data->iop.cfg));
}