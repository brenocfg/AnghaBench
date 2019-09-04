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
struct fsl_mc_io {int /*<<< orphan*/  portal_phys_addr; int /*<<< orphan*/  dev; int /*<<< orphan*/  portal_virt_addr; } ;
struct fsl_mc_command {int dummy; } ;
typedef  enum mc_cmd_status { ____Placeholder_mc_cmd_status } mc_cmd_status ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS ; 
 int /*<<< orphan*/  MC_CMD_COMPLETION_POLLING_MIN_SLEEP_USECS ; 
 int /*<<< orphan*/  MC_CMD_COMPLETION_TIMEOUT_MS ; 
 int MC_CMD_STATUS_READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 unsigned long jiffies ; 
 scalar_t__ mc_cmd_hdr_read_cmdid (struct fsl_mc_command*) ; 
 scalar_t__ mc_cmd_hdr_read_token (struct fsl_mc_command*) ; 
 int mc_read_response (int /*<<< orphan*/ ,struct fsl_mc_command*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mc_polling_wait_preemptible(struct fsl_mc_io *mc_io,
				       struct fsl_mc_command *cmd,
				       enum mc_cmd_status *mc_status)
{
	enum mc_cmd_status status;
	unsigned long jiffies_until_timeout =
		jiffies + msecs_to_jiffies(MC_CMD_COMPLETION_TIMEOUT_MS);

	/*
	 * Wait for response from the MC hardware:
	 */
	for (;;) {
		status = mc_read_response(mc_io->portal_virt_addr, cmd);
		if (status != MC_CMD_STATUS_READY)
			break;

		/*
		 * TODO: When MC command completion interrupts are supported
		 * call wait function here instead of usleep_range()
		 */
		usleep_range(MC_CMD_COMPLETION_POLLING_MIN_SLEEP_USECS,
			     MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS);

		if (time_after_eq(jiffies, jiffies_until_timeout)) {
			dev_dbg(mc_io->dev,
				"MC command timed out (portal: %pa, dprc handle: %#x, command: %#x)\n",
				 &mc_io->portal_phys_addr,
				 (unsigned int)mc_cmd_hdr_read_token(cmd),
				 (unsigned int)mc_cmd_hdr_read_cmdid(cmd));

			return -ETIMEDOUT;
		}
	}

	*mc_status = status;
	return 0;
}