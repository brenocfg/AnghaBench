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
struct ql_adapter {int /*<<< orphan*/  mpi_port_cfg_work; int /*<<< orphan*/  mpi_core_to_log; int /*<<< orphan*/  mpi_idc_work; int /*<<< orphan*/  mpi_work; int /*<<< orphan*/  mpi_reset_work; int /*<<< orphan*/  asic_reset_work; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_cancel_all_work_sync(struct ql_adapter *qdev)
{

	/* Don't kill the reset worker thread if we
	 * are in the process of recovery.
	 */
	if (test_bit(QL_ADAPTER_UP, &qdev->flags))
		cancel_delayed_work_sync(&qdev->asic_reset_work);
	cancel_delayed_work_sync(&qdev->mpi_reset_work);
	cancel_delayed_work_sync(&qdev->mpi_work);
	cancel_delayed_work_sync(&qdev->mpi_idc_work);
	cancel_delayed_work_sync(&qdev->mpi_core_to_log);
	cancel_delayed_work_sync(&qdev->mpi_port_cfg_work);
}