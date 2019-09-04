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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ETIMEDOUT ; 
 int MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS ; 
 int MC_CMD_COMPLETION_TIMEOUT_MS ; 
 int MC_CMD_STATUS_READY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 scalar_t__ mc_cmd_hdr_read_cmdid (struct fsl_mc_command*) ; 
 scalar_t__ mc_cmd_hdr_read_token (struct fsl_mc_command*) ; 
 int mc_read_response (int /*<<< orphan*/ ,struct fsl_mc_command*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mc_polling_wait_atomic(struct fsl_mc_io *mc_io,
				  struct fsl_mc_command *cmd,
				  enum mc_cmd_status *mc_status)
{
	enum mc_cmd_status status;
	unsigned long timeout_usecs = MC_CMD_COMPLETION_TIMEOUT_MS * 1000;

	BUILD_BUG_ON((MC_CMD_COMPLETION_TIMEOUT_MS * 1000) %
		     MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS != 0);

	for (;;) {
		status = mc_read_response(mc_io->portal_virt_addr, cmd);
		if (status != MC_CMD_STATUS_READY)
			break;

		udelay(MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS);
		timeout_usecs -= MC_CMD_COMPLETION_POLLING_MAX_SLEEP_USECS;
		if (timeout_usecs == 0) {
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