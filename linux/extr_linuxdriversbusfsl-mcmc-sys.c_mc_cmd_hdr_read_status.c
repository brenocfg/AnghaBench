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
struct mc_cmd_header {int /*<<< orphan*/  status; } ;
struct fsl_mc_command {int /*<<< orphan*/  header; } ;
typedef  enum mc_cmd_status { ____Placeholder_mc_cmd_status } mc_cmd_status ;

/* Variables and functions */

__attribute__((used)) static enum mc_cmd_status mc_cmd_hdr_read_status(struct fsl_mc_command *cmd)
{
	struct mc_cmd_header *hdr = (struct mc_cmd_header *)&cmd->header;

	return (enum mc_cmd_status)hdr->status;
}