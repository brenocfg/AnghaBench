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
struct TYPE_2__ {int (* reg_setup ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  num_counters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ctr ; 
 TYPE_1__* model ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  op_handle_interrupt ; 
 int op_per_cpu_rc ; 
 int /*<<< orphan*/  op_powerpc_cpu_setup ; 
 int /*<<< orphan*/  release_pmc_hardware () ; 
 int reserve_pmc_hardware (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys ; 

__attribute__((used)) static int op_powerpc_setup(void)
{
	int err;

	op_per_cpu_rc = 0;

	/* Grab the hardware */
	err = reserve_pmc_hardware(op_handle_interrupt);
	if (err)
		return err;

	/* Pre-compute the values to stuff in the hardware registers.  */
	op_per_cpu_rc = model->reg_setup(ctr, &sys, model->num_counters);

	if (op_per_cpu_rc)
		goto out;

	/* Configure the registers on all cpus.	 If an error occurs on one
	 * of the cpus, op_per_cpu_rc will be set to the error */
	on_each_cpu(op_powerpc_cpu_setup, NULL, 1);

out:	if (op_per_cpu_rc) {
		/* error on setup release the performance counter hardware */
		release_pmc_hardware();
	}

	return op_per_cpu_rc;
}