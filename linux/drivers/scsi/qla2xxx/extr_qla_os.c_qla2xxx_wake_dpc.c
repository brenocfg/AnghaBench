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
struct task_struct {int dummy; } ;
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
struct qla_hw_data {struct task_struct* dpc_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNLOADING ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

void
qla2xxx_wake_dpc(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct task_struct *t = ha->dpc_thread;

	if (!test_bit(UNLOADING, &vha->dpc_flags) && t)
		wake_up_process(t);
}