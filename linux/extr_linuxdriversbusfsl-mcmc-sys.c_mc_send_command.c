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
struct fsl_mc_io {int flags; int /*<<< orphan*/  mutex; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  portal_phys_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  portal_virt_addr; } ;
struct fsl_mc_command {int dummy; } ;
typedef  enum mc_cmd_status { ____Placeholder_mc_cmd_status } mc_cmd_status ;

/* Variables and functions */
 int EINVAL ; 
 int FSL_MC_IO_ATOMIC_CONTEXT_PORTAL ; 
 int MC_CMD_STATUS_OK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ in_irq () ; 
 scalar_t__ mc_cmd_hdr_read_cmdid (struct fsl_mc_command*) ; 
 scalar_t__ mc_cmd_hdr_read_token (struct fsl_mc_command*) ; 
 int mc_polling_wait_atomic (struct fsl_mc_io*,struct fsl_mc_command*,int*) ; 
 int mc_polling_wait_preemptible (struct fsl_mc_io*,struct fsl_mc_command*,int*) ; 
 int mc_status_to_error (int) ; 
 int /*<<< orphan*/  mc_status_to_string (int) ; 
 int /*<<< orphan*/  mc_write_command (int /*<<< orphan*/ ,struct fsl_mc_command*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mc_send_command(struct fsl_mc_io *mc_io, struct fsl_mc_command *cmd)
{
	int error;
	enum mc_cmd_status status;
	unsigned long irq_flags = 0;

	if (in_irq() && !(mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL))
		return -EINVAL;

	if (mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL)
		spin_lock_irqsave(&mc_io->spinlock, irq_flags);
	else
		mutex_lock(&mc_io->mutex);

	/*
	 * Send command to the MC hardware:
	 */
	mc_write_command(mc_io->portal_virt_addr, cmd);

	/*
	 * Wait for response from the MC hardware:
	 */
	if (!(mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL))
		error = mc_polling_wait_preemptible(mc_io, cmd, &status);
	else
		error = mc_polling_wait_atomic(mc_io, cmd, &status);

	if (error < 0)
		goto common_exit;

	if (status != MC_CMD_STATUS_OK) {
		dev_dbg(mc_io->dev,
			"MC command failed: portal: %pa, dprc handle: %#x, command: %#x, status: %s (%#x)\n",
			 &mc_io->portal_phys_addr,
			 (unsigned int)mc_cmd_hdr_read_token(cmd),
			 (unsigned int)mc_cmd_hdr_read_cmdid(cmd),
			 mc_status_to_string(status),
			 (unsigned int)status);

		error = mc_status_to_error(status);
		goto common_exit;
	}

	error = 0;
common_exit:
	if (mc_io->flags & FSL_MC_IO_ATOMIC_CONTEXT_PORTAL)
		spin_unlock_irqrestore(&mc_io->spinlock, irq_flags);
	else
		mutex_unlock(&mc_io->mutex);

	return error;
}