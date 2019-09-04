#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mce_bank {int /*<<< orphan*/  ctl; scalar_t__ init; } ;
struct TYPE_4__ {int banks; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ctl ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cmci_reenable () ; 
 int /*<<< orphan*/  cpu_info ; 
 int /*<<< orphan*/  cpuhp_tasks_frozen ; 
 TYPE_2__ mca_cfg ; 
 int /*<<< orphan*/  mce_available (int /*<<< orphan*/ ) ; 
 struct mce_bank* mce_banks ; 
 TYPE_1__ msr_ops ; 
 int /*<<< orphan*/  raw_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_reenable_cpu(void)
{
	int i;

	if (!mce_available(raw_cpu_ptr(&cpu_info)))
		return;

	if (!cpuhp_tasks_frozen)
		cmci_reenable();
	for (i = 0; i < mca_cfg.banks; i++) {
		struct mce_bank *b = &mce_banks[i];

		if (b->init)
			wrmsrl(msr_ops.ctl(i), b->ctl);
	}
}