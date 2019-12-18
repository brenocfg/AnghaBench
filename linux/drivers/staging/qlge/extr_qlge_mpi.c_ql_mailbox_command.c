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
struct ql_adapter {int /*<<< orphan*/  mpi_mutex; int /*<<< orphan*/  ndev; } ;
struct mbox_params {scalar_t__* mbox_in; int* mbox_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int CSR_CMD_CLR_R2PCI_INT ; 
 int EIO ; 
 int ETIMEDOUT ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  INTR_MASK ; 
 int INTR_MASK_PI ; 
 unsigned long MAILBOX_TIMEOUT ; 
 scalar_t__ MB_CMD_MAKE_SYS_ERR ; 
 int MB_CMD_STS_GOOD ; 
 int MB_CMD_STS_INTRMDT ; 
 int /*<<< orphan*/  drv ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_exec_mb_cmd (struct ql_adapter*,struct mbox_params*) ; 
 int ql_mpi_handler (struct ql_adapter*,struct mbox_params*) ; 
 int ql_wait_mbx_cmd_cmplt (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ql_mailbox_command(struct ql_adapter *qdev, struct mbox_params *mbcp)
{
	int status;
	unsigned long count;

	mutex_lock(&qdev->mpi_mutex);

	/* Begin polled mode for MPI */
	ql_write32(qdev, INTR_MASK, (INTR_MASK_PI << 16));

	/* Load the mailbox registers and wake up MPI RISC. */
	status = ql_exec_mb_cmd(qdev, mbcp);
	if (status)
		goto end;


	/* If we're generating a system error, then there's nothing
	 * to wait for.
	 */
	if (mbcp->mbox_in[0] == MB_CMD_MAKE_SYS_ERR)
		goto end;

	/* Wait for the command to complete. We loop
	 * here because some AEN might arrive while
	 * we're waiting for the mailbox command to
	 * complete. If more than 5 seconds expire we can
	 * assume something is wrong. */
	count = jiffies + HZ * MAILBOX_TIMEOUT;
	do {
		/* Wait for the interrupt to come in. */
		status = ql_wait_mbx_cmd_cmplt(qdev);
		if (status)
			continue;

		/* Process the event.  If it's an AEN, it
		 * will be handled in-line or a worker
		 * will be spawned. If it's our completion
		 * we will catch it below.
		 */
		status = ql_mpi_handler(qdev, mbcp);
		if (status)
			goto end;

		/* It's either the completion for our mailbox
		 * command complete or an AEN.  If it's our
		 * completion then get out.
		 */
		if (((mbcp->mbox_out[0] & 0x0000f000) ==
					MB_CMD_STS_GOOD) ||
			((mbcp->mbox_out[0] & 0x0000f000) ==
					MB_CMD_STS_INTRMDT))
			goto done;
	} while (time_before(jiffies, count));

	netif_err(qdev, drv, qdev->ndev,
		  "Timed out waiting for mailbox complete.\n");
	status = -ETIMEDOUT;
	goto end;

done:

	/* Now we can clear the interrupt condition
	 * and look at our status.
	 */
	ql_write32(qdev, CSR, CSR_CMD_CLR_R2PCI_INT);

	if (((mbcp->mbox_out[0] & 0x0000f000) !=
					MB_CMD_STS_GOOD) &&
		((mbcp->mbox_out[0] & 0x0000f000) !=
					MB_CMD_STS_INTRMDT)) {
		status = -EIO;
	}
end:
	/* End polled mode for MPI */
	ql_write32(qdev, INTR_MASK, (INTR_MASK_PI << 16) | INTR_MASK_PI);
	mutex_unlock(&qdev->mpi_mutex);
	return status;
}