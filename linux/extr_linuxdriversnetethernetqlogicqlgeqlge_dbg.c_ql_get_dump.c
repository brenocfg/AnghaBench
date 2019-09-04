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
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_FRC_COREDUMP ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ql_core_dump (struct ql_adapter*,void*) ; 
 int /*<<< orphan*/  ql_gen_reg_dump (struct ql_adapter*,void*) ; 
 int /*<<< orphan*/  ql_get_core_dump (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_soft_reset_mpi_risc (struct ql_adapter*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ql_get_dump(struct ql_adapter *qdev, void *buff)
{
	/*
	 * If the dump has already been taken and is stored
	 * in our internal buffer and if force dump is set then
	 * just start the spool to dump it to the log file
	 * and also, take a snapshot of the general regs to
	 * to the user's buffer or else take complete dump
	 * to the user's buffer if force is not set.
	 */

	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags)) {
		if (!ql_core_dump(qdev, buff))
			ql_soft_reset_mpi_risc(qdev);
		else
			netif_err(qdev, drv, qdev->ndev, "coredump failed!\n");
	} else {
		ql_gen_reg_dump(qdev, buff);
		ql_get_core_dump(qdev);
	}
}