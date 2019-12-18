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
struct ql_adapter {scalar_t__ mailbox_in; } ;
struct mbox_params {int in_count; int /*<<< orphan*/ * mbox_in; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  CSR_CMD_SET_H2R_INT ; 
 int CSR_HRI ; 
 int EIO ; 
 int /*<<< orphan*/  SEM_PROC_REG_MASK ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ql_write_mpi_reg (struct ql_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_exec_mb_cmd(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int i, status;

	/*
	 * Make sure there's nothing pending.
	 * This shouldn't happen.
	 */
	if (ql_read32(qdev, CSR) & CSR_HRI)
		return -EIO;

	status = ql_sem_spinlock(qdev, SEM_PROC_REG_MASK);
	if (status)
		return status;

	/*
	 * Fill the outbound mailboxes.
	 */
	for (i = 0; i < mbcp->in_count; i++) {
		status = ql_write_mpi_reg(qdev, qdev->mailbox_in + i,
						mbcp->mbox_in[i]);
		if (status)
			goto end;
	}
	/*
	 * Wake up the MPI firmware.
	 */
	ql_write32(qdev, CSR, CSR_CMD_SET_H2R_INT);
end:
	ql_sem_unlock(qdev, SEM_PROC_REG_MASK);
	return status;
}