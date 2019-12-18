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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fsl_mc_io {int dummy; } ;
struct fsl_mc_command {scalar_t__ params; int /*<<< orphan*/  header; int /*<<< orphan*/  member_0; } ;
struct dpio_stashing_dest {int /*<<< orphan*/  sdest; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPIO_CMDID_SET_STASHING_DEST ; 
 int /*<<< orphan*/  mc_encode_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mc_send_command (struct fsl_mc_io*,struct fsl_mc_command*) ; 

int dpio_set_stashing_destination(struct fsl_mc_io *mc_io,
				  u32 cmd_flags,
				  u16 token,
				  u8 sdest)
{
	struct fsl_mc_command cmd = { 0 };
	struct dpio_stashing_dest *dpio_cmd;

	cmd.header = mc_encode_cmd_header(DPIO_CMDID_SET_STASHING_DEST,
					  cmd_flags, token);
	dpio_cmd = (struct dpio_stashing_dest *)cmd.params;
	dpio_cmd->sdest = sdest;

	return mc_send_command(mc_io, &cmd);
}