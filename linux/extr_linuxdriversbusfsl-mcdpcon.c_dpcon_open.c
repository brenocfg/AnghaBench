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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpcon_cmd_open {int /*<<< orphan*/  dpcon_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPCON_CMDID_OPEN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  mc_cmd_hdr_read_token (struct fsl_mc_command*) ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpcon_open(struct fsl_mc_io *mc_io,
	       u32 cmd_flags,
	       int dpcon_id,
	       u16 *token)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpcon_cmd_open *dpcon_cmd;
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPCON_CMDID_OPEN,
					  cmd_flags,
					  0);
	dpcon_cmd = (struct dpcon_cmd_open *)cmd.params;
	dpcon_cmd->dpcon_id = cpu_to_le32(dpcon_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_read_token(&cmd);

	return 0;
}